#include "randomgenerator.hpp"

RandomPointGenerator::RandomPointGenerator(int width, int height, int block_size_offset):
m_random_seed(), m_random_generator(m_random_seed()), 
m_random_width_range(0, width - block_size_offset), m_random_height_range(0, height - block_size_offset)
{}

RandomPointGenerator::~RandomPointGenerator()
{}

int RandomPointGenerator::GetRandomWidth()
{
    return m_random_width_range(m_random_generator);
}

int RandomPointGenerator::GetRandomHeight()
{
    return m_random_height_range(m_random_generator);
}
