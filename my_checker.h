#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
#include <typeinfo>
#define debug printf("in c.cpp line %d\n",__LINE__);
// using namespace std;

namespace ftc {
	// OK 2020-12-12
	inline bool is_num(char c) {
		// 0~9 .
		return (c >= '0' && c <= '9') || c == '.';
	}
	// OK 2020-12-12
	inline bool is_word(char c) {
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
	}
	// OK 2020-12-12
	inline bool is_split(char c) {
		return !is_num(c) && !is_word(c);
	}
	template <class VerT, class WeightT> class Checker;

	struct Error {
		int line;
		std::string message;
		Error(int l, const std::string& msg) :
			line(l), message(msg) {}
		void print_error()const noexcept {
			std::cerr << "error in line " << line << '\n';
			std::cerr << "error message: " << message << std::endl;
		}
	};

	// OK 2020-12-12
	template<class VerT, class WeightT>
	struct Edge {
		VerT from, to;
		WeightT weight;
		void print_edge()const noexcept {
			std::cout << from << " -> " << to << "  w = " << weight << '\n';
		}
		Edge(VerT f, VerT t, WeightT w) :from(f), to(t), weight(w) {}
	};
	// OK 2020-12-16
	inline std::vector<std::string> split(const std::string& str)noexcept {
		std::vector<std::string> ans;
		for (size_t i = 0; i < str.length(); i++) {
			while (i < str.length() && is_split(str[i])) i++;
			auto prev_i = i;
			while (i < str.length() && !is_split(str[i])) i++;
			if (i > prev_i)
				ans.push_back(std::move(str.substr(prev_i, i - prev_i)));
		}
		return std::move(ans);
	}
	template <class VerT, class WeightT>
	class Checker {
	private:
		std::map<VerT, std::vector<Edge<VerT, WeightT>> > edges;// edge<WeightT> 存的[结点原始编号]
		std::set<VerT> raw_node;
		std::map<VerT, int> node_to_base;
		int max_base;
        WeightT total_weight;
		WeightT run() const noexcept {
			WeightT loss = (WeightT)0;
			for (const auto& key_value : edges) {
				// auto& vct_edge = key_value.second;
				for (const auto& edge : key_value.second) {
					if (node_to_base.at(edge.from) != node_to_base.at(edge.to))
						loss += edge.weight;
				}
			}
			return loss;
		}
		bool is_safe_ver(VerT ver) const{
			return raw_node.find(ver) != raw_node.cend();
		}
	public:
        WeightT get_total_weight() const {
            return this->total_weight;
        }
		Checker(const std::string& GraphFileName) :
			max_base(0), total_weight(0.0)
		{
			std::fstream fs;
			fs.open(GraphFileName);
			if (!fs.good())
				throw Error(__LINE__, "open file error");
			// else printf("successfully open %s\n",GraphFileName.c_str());
			std::string str;
			while (std::getline(fs, str)) {
				auto str_split = split(str);
				if (str_split.empty()) continue;
				if (str_split.size() == 1) {
					VerT num;
					if constexpr (std::is_same_v<VerT, int>)
						num = atoi(str_split[0].c_str());
					else if constexpr (std::is_same_v<VerT, std::string>)
						num = str_split[0];
					else throw Error(__LINE__, "type error");
					raw_node.insert(num);
					edges.insert(std::make_pair(num, std::vector<Edge<VerT, WeightT>>()));
				}
				else if (str_split.size() == 3) {
					VerT to, from;
					if constexpr (std::is_same_v<VerT, int>) {
						from = atoi(str_split[0].c_str());
						to = atoi(str_split[1].c_str());
					}
					else if constexpr (std::is_same_v<VerT, std::string>) {
						from = str_split[0];
						to = str_split[1];
					}
					else throw Error(__LINE__, "type error");
					// std::cout << from << " -> " << to << std::endl;
					raw_node.insert(from);
					raw_node.insert(to);
					WeightT weight;
					if constexpr (std::is_same_v<WeightT, double>) {
						// printf("WeightT == double\n");
						weight = (WeightT)atof(str_split[2].c_str());
					}
					else if constexpr (std::is_same_v<WeightT, int>) {
						// printf("WeightT == int\n");
						weight = (WeightT)atoi(str_split[2].c_str());
					}
					else {
						fs.close();
						throw Error(__LINE__, "type error");
					}

					{// control result1
						// 无向边 from -> to
						Edge<VerT, WeightT> e(from, to, weight);
						this->total_weight += weight;
						auto result1 = edges.insert(std::make_pair(from, std::vector<Edge<VerT, WeightT>>{e}));
						if (!result1.second) {
							// 如果没有插入成功
							// e.print_edge();
							(result1.first->second).push_back(e);
						}
						edges.insert(std::make_pair(to, std::vector<Edge<VerT,WeightT>>()));
					}
				}
				else {
					fs.close();
					throw Error(__LINE__, "format error");
				}
			}// end while getline
			fs.close();
		}
        std::string check(const std::string& filename) {
            this->clear();
			std::fstream fs;
			fs.open(filename, std::ios::in);
			if (!fs.good()) {
				throw Error(__LINE__, "open file error");
			}
			std::string str;
			max_base = 0;
			int count = 0, max_size = 0;
			while (std::getline(fs, str)) {
				auto split_str = split(str);
				max_size = std::max(max_size, (int)split_str.size());
				if (split_str.empty()) continue;
				for (auto& s : split_str) {
					VerT node;
					if constexpr (std::is_same_v<VerT, int>)
						node = atoi(s.c_str());
					else node = s;
					// printf("read %d\n",node);
					if (raw_node.find(node) == raw_node.cend()) {
						fs.close();
						if constexpr (std::is_same_v<VerT, int>)
							throw Error(__LINE__, "node '" + std::to_string(node) + "' number error");
						else
							throw Error(__LINE__, "node '" + node + "' number error");
					}
					++count;
					auto result = node_to_base.insert(std::pair<VerT, int>(node, max_base));
					if (!result.second) {
						fs.close();
						if constexpr (std::is_same_v<VerT, int>)
							throw Error(__LINE__, std::string("double node '") + std::to_string(node) + std::string("'"));
						else throw Error(__LINE__, std::string("double node '") + node + std::string("'"));
					}
					raw_node.insert(node);
				}

				++max_base;
			}// end while(getline)
			fs.close();
			if (count != raw_node.size()) {
				// printf("count = %d, nodesize = %d\n",count,raw_node.size());
				throw Error(__LINE__, "node don't exist");
			}
			WeightT loss = run();
            std::string out;
            out += "loss / total = " + std::to_string(loss) + " / " + std::to_string(total_weight)+ '\n';
            out += "max subGraph size = " + std::to_string(max_size);
            return move(out);
		}
        void clear(){
            max_base = 0;
            node_to_base.clear();
        }
		bool unicom(VerT ver1, VerT ver2) const {
		if(!is_safe_ver(ver1)||!is_safe_ver(ver2)){
			throw Error(__LINE__,"Ver don't exist");
		}
        //std::cout << "check " << ver1 << " , " << ver2 << std::endl;
		std::set<VerT> vis;
		// bfs
		std::queue<VerT> q;
		q.push(ver1);
		while(!q.empty()){
			VerT tmp_ver = q.front(); q.pop();
			if(tmp_ver == ver2) return true;
			if(vis.find(tmp_ver) != vis.cend()) continue;
			vis.insert(tmp_ver);
            // std::cout << "tmp_ver = " << tmp_ver << std::endl;
			for(auto edge_iter=edges.at(tmp_ver).cbegin();edge_iter!=edges.at(tmp_ver).cend();edge_iter++){
				// 如果连的点没有vis，就丢入queue
				if(vis.find(edge_iter->to) == vis.cend())
					q.push(edge_iter->to);
			}
		}
		return false;
	}
	WeightT min_dist(VerT u, VerT v) const {
		if(!unicom(u, v)){
			throw Error(__LINE__, "vers don't unicom");
		}
		const auto iter_u = edges.find(u);
		const auto iter_v = edges.find(v);
		if(iter_u==edges.cend()||iter_v==edges.cend()){
			throw Error(__LINE__, "Node don't exist!");
		}
		// dijkstra
		std::map<VerT, WeightT> dist;
		std::queue<std::pair<VerT, WeightT> > q;
		q.push(std::make_pair(u, (WeightT)0));
		while(!q.empty()){
			std::pair<VerT, WeightT> curr_node = q.front(); q.pop();
			auto iter_dist = dist.find(curr_node.first);
			if(iter_dist != dist.cend() && iter_dist->second < curr_node.second)
				continue;
			dist[curr_node.first] = curr_node.second;
			for(auto edge_iter=edges.at(curr_node.first).cbegin();edge_iter!=edges.at(curr_node.first).cend();edge_iter++){
			// for(Edge<VerT,WeightT>& edge: edges[curr_node.first]){
				VerT to = edge_iter->to;
				q.push(std::make_pair(to, curr_node.second + edge_iter->weight));
			}
		}
		if(dist.find(v)==dist.cend()){
			throw Error(__LINE__, "graph don't unicom");
		}
		else return dist[v];
	}
	};// end class Checker



}// end namespace ftc

#undef debug
