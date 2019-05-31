#pragma once
#include "pch.h"
#include "agent.h"
#include<vector>
#include<random>
#include "flappy.h"



class AgentPopulation {
public:
	AgentPopulation(int populationCount,int levelLength,std::mt19937 & rng);
	void ComputeFitness(const LevelDescription & level);
	void CreateNextGeneration(int numberOfPartitions,int partitionSize,int levelLength,int mutationProbability, std::mt19937 & rng);
	void CrossoverAndMutationInsidePartition(int partitionNumber, int startingIndex, int numberOfLoops,int mutationProbability,std::mt19937 & rng);
	void CrossoverAndMutatePartitions(int numberOfPartitions,int partitionSize,int levelLength,int mutationProbability,std::mt19937 & rng);
	void SortAgents(const LevelDescription & level);
	bool LevelPassed(int levelLength) const;
	Agent ReturnFirstSolution();

	void Print() const;
private:

	std::vector<Agent> m_agentsPopulation;
	

};