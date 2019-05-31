#include "pch.h"
#include "agent.h"
#include "bird.h"


//to be removed
#include <iostream>
bool CompareAgents(const Agent & agentOne, const Agent & agentTwo)
{
	return agentOne.m_fitnessScore > agentTwo.m_fitnessScore;
}


Agent::Agent()
{
	m_fitnessScore = 0;
}



//Function works
void Agent::GenerateRandomDecision(int levelLength, std::mt19937 & rng)
{
	m_agentDecisions.reserve(levelLength);
	std::uniform_int_distribution<int> dist(0, 1);
	for (int i = 0;i < levelLength;++i) {
		m_agentDecisions.push_back(dist(rng));
	}

}

// changes a random chromosome 
void Agent::MutateAgent(int levelLength,std::mt19937 & rng)
{
	std::uniform_int_distribution<int> dist(0,levelLength-1);
	int mutationIndexOne = dist(rng);
	m_agentDecisions[mutationIndexOne] = !m_agentDecisions[mutationIndexOne];

}

// Changes chromosomes between two agents after a certain point
void Crossover(Agent & firstParent, Agent & secondParent, int crossoverPoint)
{
	for (int i = crossoverPoint;i<firstParent.m_agentDecisions.size();++i) {
		int temp = firstParent.m_agentDecisions[i];
		firstParent.m_agentDecisions[i] = secondParent.m_agentDecisions[i];
		secondParent.m_agentDecisions[i] = temp;
	}
	
}





bool Agent::LevelPassed(int levelLength) const
{
	return m_fitnessScore == levelLength;
}

int Agent::GetFitnessScore() const 
{
	return m_fitnessScore;
}

std::vector<int> Agent::GetDecisionsVector() const 
{
	return m_agentDecisions;
}
int Agent::GetLevelLength() const
{
	return m_agentDecisions.size();
}

void Agent::ComputeAgentFitness(const LevelDescription & level)
{
	int fitnessScore = 0;
	Bird bird({ 0,level.height / 2 });
	
	
	// Or should i do a while loop?
	for (int i = 0;i < level.length/HORIZONTAL_VELOCITY;++i) {
		if (bird.IsAlive(level)) {
			++fitnessScore;
			bird.NextPosition(m_agentDecisions[i]);
		}
		else {
			break;
		}
	}
	m_fitnessScore = fitnessScore;
}

void Agent::Print() const 
{
	for (int i = 0;i < m_agentDecisions.size();++i) {
		std::cout << m_agentDecisions[i] << " ";
	}
	std::cout << "\n";
}