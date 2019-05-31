#include "pch.h"
#include "geneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(const LevelDescription & level) :
	m_level(level),
	rng(10),
	m_agentPop(m_populationCount,m_level.length/HORIZONTAL_VELOCITY,rng)
{
	
}

void GeneticAlgorithm::GenerateSolution()
{
	int levelLength = m_level.length / HORIZONTAL_VELOCITY;
	m_agentPop.ComputeFitness(m_level);
	m_agentPop.SortAgents(m_level);

	while (!(LevelPassed(levelLength))) {
		m_agentPop.CreateNextGeneration(m_numberOfPartitions, m_partitionSize, levelLength, m_mutationProb, rng);
		m_agentPop.ComputeFitness(m_level);
		m_agentPop.SortAgents(m_level);
	}

}

bool GeneticAlgorithm::LevelPassed(int levelLength) const
{
	return m_agentPop.LevelPassed(levelLength);
}

Agent GeneticAlgorithm::ReturnSolution()
{
	return m_agentPop.ReturnFirstSolution();
}
