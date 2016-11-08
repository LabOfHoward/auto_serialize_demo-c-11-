#pragma  once
#include <string> 
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

namespace StringParse{
	//�ָ��ַ���
	std::vector<std::string> split(std::string str, std::string pattern)
	{
		std::string::size_type pos;
		std::vector<std::string> result;
		str += pattern;//��չ�ַ����Է������
		auto size = str.size();

		for (auto i = 0; i < size; i++)
		{
			pos = str.find(pattern, i);
			if (pos < size)
			{
				std::string s = str.substr(i, pos - i);
				result.push_back(s);
				i = pos + pattern.size() - 1;
			}
		}
		return result;
	}

	//����ת�ַ���
	
	template<typename T>
	string ToString(const T& v, int indent = 0){ 
		return v.ToString(indent); 
	}
	template<> string ToString(const int& v, int indent){ return  to_string(v); }
	template<> string ToString(const long long& v, int indent){ return  to_string(v); }
	template<> string ToString(const float& v, int indent){ return  to_string(v); }
	template<> string ToString(const bool& v, int indent){ return  v ? "true" : "false"; }
	template<> string ToString(const string& v, int indent){ return  v; }
	template<typename T, typename... Args>
	string ToString(int indent, int idx, const T &t, const Args&... args) {
		static string s_indentSplit[] = { ",", "|", ":", ";", "^" };
		string s = ToString(t, indent + 1);
		s += s_indentSplit[indent + 1];
		s +=ToString(indent, idx+1,args...);//�ݹ�
		return s;
	}
	template<typename T>
	string ToString(int indent, int idx, const T &t) {//������ܺ������(const int& v, int indent)��ͻ�����ԼӶ��idx����
		return ToString(t, indent + 1);
	}
	template<typename T>
	string ToString(const std::vector<T>& v, int indent=0){//��Ȼͬ��ֻ��һ��ģ�����������c++����������vector<T>��ʱ�������ʶ�����������T
		static string s_indentSplit[] = { ",", "|", ":", ";", "^" };

		string s = "";
		auto begin = v.begin();
		while (begin != v.end())
		{
			if (begin != v.begin())
				s += s_indentSplit[indent];
			s += ToString<T>(*begin,indent+1);
			++begin;
		}
		return s;
	}
	template<typename K, typename V>
	string ToString(const std::map<K,V>& v, int indent=0){//��Ȼͬ��ֻ��һ��ģ�����������c++����������map<T>��ʱ�������ʶ�����������T
		static string s_indentSplit[] = { ",", "|", ":", ";", "^" };

		string s = "";
		auto begin = v.begin();
		while (begin != v.end())
		{
			if (begin != v.begin())
				s += s_indentSplit[indent];
			s += ToString<K>(begin->first, indent + 2);
			s += s_indentSplit[indent+1];
			s += ToString<V>(begin->second, indent + 2);
			++begin;
		}
		return s;
	}
	template<typename K, typename V>
	string ToString(const std::unordered_map<K, V>& v, int indent = 0){//��Ȼͬ��ֻ��һ��ģ�����������c++����������unordered_map<T>��ʱ�������ʶ�����������T
		static string s_indentSplit[] = { ",", "|", ":", ";", "^" };

		string s = "";
		auto begin = v.begin();
		while (begin != v.end())
		{
			if (begin != v.begin())
				s += s_indentSplit[indent];
			s += ToString<K>(begin->first, indent + 2);
			s += s_indentSplit[indent + 1];
			s += ToString<V>(begin->second, indent + 2);
			++begin;
		}
		return s;
	}

	//�ַ���ת�������ģ�塣һ����������Ҫ֧�����л������ԼӺ꣬Ҳ����д��ģ�庯��
	template<typename T>
	void ToObject(const string& s, T& v, int indent = 0){ v.ToObject(s, indent); }
	template<> void ToObject(const string& s, int& v, int indent){ v = stoi(s); }
	template<> void ToObject(const string& s, long long& v, int indent){ v = stoll(s); }
	template<> void ToObject(const string& s, float& v, int indent){ v = stof(s); }
	template<> void ToObject(const string& s, bool& v, int indent){ v = s == "true" || s == "1"; }
	template<> void ToObject(const string& s, string& v, int indent){ v = s; }
	template<typename T,typename... Args>
	void ToObject(int indent, vector<string> & ss,int idx,T &t, Args&... args)	{
		ToObject(indent, ss, idx+1, args...);//�ݹ�
		ToObject(ss[idx], t,indent+1);
	}
	template<typename T>
	void ToObject(int indent, vector<string> & ss, int idx, T &t) {
		ToObject(ss[idx], t, indent + 1);
	}

	template<typename T>
	void ToObject(const string& s, std::vector<T>& v, int indent = 0){//��Ȼͬ��ֻ��һ��ģ�����������c++����������vector<T>��ʱ�������ʶ�����������T
		static string s_indentSplit[] = { ",", "|", ":", ";", "^" };

		v.clear();
		vector<string> ss = split(s, s_indentSplit[indent]);
		if (ss.size() == 0)
			return;
		T element = T();
		v.assign(ss.size(), element);
		for (auto i = 0; i < ss.size(); ++i){
			ToObject<T>(ss[i], v[i], indent + 1);
		}
	}
	template<typename K, typename V>
	void ToObject(const string& s, std::map<K, V>& v, int indent = 0){//��Ȼͬ��ֻ��һ��ģ�����������c++����������map<T>��ʱ�������ʶ�����������T
		static string s_indentSplit[] = { ",", "|", ":", ";", "^" };

		v.clear();
		vector<string> ss = split(s, s_indentSplit[indent]);
		indent++;
		if (ss.size() == 0)
			return;
		for (auto i = 0; i < ss.size(); ++i){
			vector<string> pairStr = split(ss[i], s_indentSplit[indent]);
			if (pairStr.size() != 2){
				std::cout << "����map��ʱ�����" << s << std::endl;
				continue;
			}
			K key;
			V value;
			ToObject<K>(pairStr[0], key, indent + 1);
			ToObject<V>(pairStr[1], value, indent + 1);
			v[key]=value;
		}
	}
	template<typename K, typename V>
	void ToObject(const string& s, std::unordered_map<K, V>& v, int indent = 0){//��Ȼͬ��ֻ��һ��ģ�����������c++����������unordered_map<T>��ʱ�������ʶ�����������T
		static string s_indentSplit[] = { ",", "|", ":", ";", "^" };

		v.clear();
		vector<string> ss = split(s, s_indentSplit[indent]);
		indent++;
		if (ss.size() == 0)
			return;
		for (auto i = 0; i < ss.size(); ++i){
			vector<string> pairStr = split(ss[i], s_indentSplit[indent]);
			if (pairStr.size() != 2){
				std::cout << "����map��ʱ�����" << s << std::endl;
				continue;
			}
			K key;
			V value;
			ToObject<K>(pairStr[0], key, indent + 1);
			ToObject<V>(pairStr[1], value, indent + 1);
			v[key] = value;
		}
	}
	

	////Ԫ�������
	//template <typename Tuple, std::size_t N>
	//struct ParseTuple {
	//	static void ToObject(vector<string> & ss, Tuple& t, int indent)
	//	{
	//		ParseTuple<Tuple, N - 1>::ToObject(ss, t, indent);
	//		if (N < ss.size())
	//			StringParse::ToObject(ss[N], std::get<N>(t), indent+1);
	//	}

	//	static string ToString( Tuple& t,int indent){
	//		static string s_indentSplit[] = { ",", "|", ":", ";", "^" };
	//		string s1 = ParseTuple<Tuple, N - 1>::ToString( t, indent);
	//		string s2= StringParse::ToString( std::get<N>(t), indent + 1);
	//		return s1 + s_indentSplit[indent ] + s2;
	//	}
	//};

	//template <typename Tuple>
	//struct ParseTuple<Tuple, 0> {
	//	static void ToObject(vector<string> & ss, Tuple& t, int indent)
	//	{
	//		StringParse::ToObject(ss[0], std::get<0>(t), indent+1);
	//	}
	//	static string ToString( Tuple& t,int indent){
	//		return StringParse::ToString(std::get<0>(t), indent+1);
	//	}
	//};
	//template<typename... Args> string ToString(int indent, const Args&... args)const
	//{
		//const std::tuple<const Args&...>& t = std::tuple<const Args&...>(args...);
		//return StringParse::ParseTuple<const std::tuple<const Args&...>, sizeof...(Args)-1>::ToString(t, indent);
	//}
}


#define STRING_PARSE(...) \
void ToObject(const string& s, int indent)\
{\
	static string s_indentSplit[] = { ",", "|", ":", ";", "^" }; \
	auto ss = StringParse::split(s, s_indentSplit[indent]); \
	if (ss.size() == 0)\
		return; \
	StringParse::ToObject(indent, ss,0,__VA_ARGS__);\
}\
string ToString(int indent) const\
{\
	return StringParse::ToString(indent,0, __VA_ARGS__);\
}
