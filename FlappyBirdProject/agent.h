#pragma once
#include "pch.h"
#include "flappy.h"

#include<vector>
#include<random>



class Agent {
public:
	

	Agent();
	void GenerateRandomDecision(int levelLength,std::mt19937 & rng);
	void ComputeAgentFitness(const LevelDescription & level);
	void MutateAgent(int levelLength,std::mt19937& rng);
	bool LevelPassed(int levelLength) const;
	int GetFitnessScore()const ;
	std::vector<int> GetDecisionsVector() const ;
	friend void Crossover(Agent & firstParent, Agent & secondParent, int crossoverPoint); //function which gives us crossover
	friend bool CompareAgents(const Agent& agentOne, const Agent& agentTwo);
	int GetLevelLength() const;


	
	

	void Print() const ;
private:
	std::vector<int> m_agentDecisions;
	int m_fitnessScore;

};


bool CompareAgents(const Agent& agentOne, const Agent& agentTwo);
void Crossover(Agent & firstParent, Agent & secondParent, int crossoverPoint);
