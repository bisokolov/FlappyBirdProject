#pragma once
#include "pch.h"
#include "flappy.h"
#include "agentPopulation.h"
#include<random>

class GeneticAlgorithm {
public:
	GeneticAlgorithm(const LevelDescription & level);
	void GenerateSolution();
	Agent ReturnSolution();
private:
	bool LevelPassed(int levelLength) const;
	const int m_populationCount = 100; //100
	LevelDescription m_level;
	std::mt19937 rng;
	AgentPopulation m_agentPop;
	
	const int m_numberOfPartitions = 4; //4
	const int m_partitionSize = m_populationCount / m_numberOfPartitions;
	const int m_mutationProb = 4;
};

