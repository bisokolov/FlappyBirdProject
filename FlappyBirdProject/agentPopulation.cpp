#include "pch.h"
#include "agentPopulation.h"
#include "agent.h"
#include <iostream>

AgentPopulation::AgentPopulation(int populationCount,int levelLength,std::mt19937 & rng)
{
	m_agentsPopulation.reserve(populationCount);
	for (int i = 0;i < populationCount;++i) {
		Agent ag;
		ag.GenerateRandomDecision(levelLength, rng);
		m_agentsPopulation.push_back(ag);
	}
}

void AgentPopulation::ComputeFitness(const LevelDescription & level)
{
	for (int i = 0;i < m_agentsPopulation.size();++i) {
		m_agentsPopulation[i].ComputeAgentFitness(level);
	}
}

void AgentPopulation::CreateNextGeneration(int numberOfPartitions, int partitionSize, int levelLength,int mutationProbability, std::mt19937 & rng)
{
	for (int i = 0;i < partitionSize;++i) {
		for (int j = 1;j < numberOfPartitions;++j) {
			int offset = j * partitionSize;
			m_agentsPopulation[offset + i] = m_agentsPopulation[i];
		}
	}
	CrossoverAndMutatePartitions(numberOfPartitions, partitionSize, levelLength, mutationProbability, rng);
}

// numberOfLoops = intervalSize/partitionIndex*2
void AgentPopulation::CrossoverAndMutationInsidePartition(int partitionIndex, int startingIndex, int numberOfLoops,int mutationProbability, std::mt19937 & rng)
{
	for (int i = 0;i < numberOfLoops*partitionIndex*2;i += 2 * partitionIndex) {
		for (int j = 0;j < partitionIndex;++j) {

			std::uniform_int_distribution<int> crossoverDist(m_agentsPopulation[0].GetLevelLength() / 3, (m_agentsPopulation[0].GetLevelLength() / 3) * 2);
			int crossoverPoint = crossoverDist(rng);
			Crossover(m_agentsPopulation[startingIndex + i + j], m_agentsPopulation[startingIndex + i + j + partitionIndex], crossoverPoint);

			//mutateWithProbability 2%
			std::uniform_int_distribution<int> mutationDist(0, 99);
			int mutation = mutationDist(rng);
			if (mutation < mutationProbability) {
				m_agentsPopulation[startingIndex + i + j].MutateAgent(m_agentsPopulation[0].GetLevelLength(), rng);
			}
			mutation = mutationDist(rng);
			if (mutation < mutationProbability) {
				m_agentsPopulation[startingIndex + i + j + partitionIndex].MutateAgent(m_agentsPopulation[0].GetLevelLength(), rng);
			}

		}
	}
	
}

void AgentPopulation::CrossoverAndMutatePartitions(int numberOfPartitions, int partitionSize,int levelLength,int mutationProbability, std::mt19937 & rng)
{
	for (int partitionNumber = 1;partitionNumber < numberOfPartitions;++partitionNumber) {
		int startingIndexOfPartition = partitionNumber * partitionSize;
		int numberOfLoops = partitionSize / (2 * partitionNumber);
		CrossoverAndMutationInsidePartition(partitionNumber, startingIndexOfPartition, numberOfLoops,mutationProbability,rng);
		
	
		int remainder = partitionSize - numberOfLoops * partitionNumber * 2;
		if (remainder > 0) {
			int remainderIndex = (partitionNumber + 1) * partitionSize;
			for (int i = remainder; i > 0;--i) {
				m_agentsPopulation[remainderIndex - i].MutateAgent(levelLength, rng);
			}
		}

		
	}
}



//Todo:: The sort function
void AgentPopulation::SortAgents(const LevelDescription & level) {
	std::sort(m_agentsPopulation.begin(), m_agentsPopulation.end(), CompareAgents);
}

bool AgentPopulation::LevelPassed(int levelLength) const
{
	for (int i = 0;i < m_agentsPopulation.size();++i) {
		if (m_agentsPopulation[i].LevelPassed(levelLength)) {
			return true;
		}
	}
	return false;
}

Agent AgentPopulation::ReturnFirstSolution()
{
	return m_agentsPopulation[0];
}

void AgentPopulation::Print() const
{
	std::cout << "Printing population \n";
	for (int i = 0;i < m_agentsPopulation.size();++i) {
		m_agentsPopulation[i].Print();
	}
}
