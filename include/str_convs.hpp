#include <iostream>
#include <sstream>
#include <set>
#include <map>

template<typename ContainerType>
void pushback(ContainerType &L, const typename ContainerType::value_type &e) {
	L.push_back(e);
}

template<typename ElementType>
void pushback(std::set<ElementType> &S, const ElementType &e) {
	S.insert(e);
}


template<typename T> 
T str2T(const std::string &str) {
	std::stringstream ss(str); T aux; ss>>aux; return aux;
}

template<> 
std::string str2T(const std::string &str) {
	if (!str.empty() && (str[0]=='\''||str[1]=='\"')) return str.substr(1,str.size()-2);
	return str;
}

template<class ContainerType>
ContainerType str2cont(const std::string &str, char cbeg='{', char cend='}', char csep=',') {
	ContainerType L;
	size_t i=0, l=str.size();
	if (!str.empty() && str[i]==cbeg) ++i, --l;
	for(size_t p0=i,nest=0;i<=l;++i) {
    if (nest==0 && (i==l||str[i]==csep)) { // elements' separator
      size_t p1 = i;
      while (p1>p0 && (str[p1-1]==' '||str[p1-1]=='\n'||str[p1]-1=='\t')); // left-trimming
      if (p0!=p1) pushback(L,str2T<typename ContainerType::value_type>(str.substr(p0,p1-p0))); p0=p1+1;
    }
		else if (i==p0 && (str[i]==' '||str[i]=='\t'||str[i]=='\n')) p0++; // right-trimming
		else if (str[i]==cbeg) ++nest; else if (str[i]==cend) --nest; // nested lists
	}
	return L;
}

template<typename SetType>
std::map<typename SetType::value_type,SetType> str2graph(const std::string str) {
	std::map<typename SetType::value_type,SetType> G;
	for(auto s : str2cont<std::list<std::string>>(str)) {
		auto pos = s.find("->");
		G[str2T<typename SetType::value_type>(s.substr(0,pos))] = str2cont<SetType>(s.substr(pos+2));
	}
	return G;
}

template<typename MapType>
std::string graph2str(const MapType &G, bool pretty = false) {
	std::stringstream ss;
	bool first_key = true;
	for(const auto &p:G) {
		if (!first_key) { if (pretty) ss << ",\n"; else ss << ", "; } first_key = false;
		if (pretty) ss << p.first << " -> { "; else ss << p.first << "->{";
		bool first_vec = true;
		for(auto x:p.second) {
			if (!first_vec) { if (pretty) ss << ", "; else ss << ","; } first_vec = false;
			ss << x;
		}
		if (pretty) ss << " }"; else ss << "}";
	};
	return ss.str();
}

template<class ContainerType>
std::string cont2str(const ContainerType &L, char cbeg='{', char cend='}', char csep=',') {
  std::stringstream ss;
  auto it=L.begin();
  if (it==L.end()) ss << cbeg; 
  else while (it!=L.end())
      ss<<(it==L.begin()?cbeg:csep)<<*(it++);
  ss<<cend;
  return ss.str();
}
