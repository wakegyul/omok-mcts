#pragma once
#include "MonteCarloNode.h"


class MonteCarloTree {
public:
	MonteCarloTree(const Omok& omok, Turn ai_turn, double exploration_parameter)
		:ai_turn_(ai_turn), exploration_parameter_(exploration_parameter), rollout_cnt_(0) {
		root_ = new MonteCarloNode(omok, Move{ ai_turn_,0,0 }, exploration_parameter);
	}
	// 시뮬레이션 시작 전, 부분 트리 복사하여 병렬 실행 위함
	MonteCarloTree(const MonteCarloTree& other)
		:ai_turn_(other.ai_turn_), exploration_parameter_(other.exploration_parameter_), rollout_cnt_(other.rollout_cnt_) {
		// 부분 트리 복사
		root_ = new MonteCarloNode(*other.root_);
	}
	~MonteCarloTree() {
		//std::thread t(&MonteCarloTree::MonteCarloNode::FreeTreeNode, root_);
		//t.detach();
		root_->FreeTreeNode();
	}

	void AddNodesUntilMaxDepth(uint max_depth);
	Move GetMctsBestMove();
	void InitialRollout();
	void Print();

private:
	// Recursive: 각 노드마다 child를 더해줌
	void RecursiveAddNodesUntilMaxDepth(MonteCarloNode* node, uint cur_depth, uint max_depth);
	void PrintRootAndChildrenMapAndUct(MonteCarloNode* best_node);

	MonteCarloNode* root_;
	Turn ai_turn_;
	double exploration_parameter_;
	uint rollout_cnt_;
};