#ifndef __RANDOM_GENERATOR__
#define __RANDOM_GENERATOR__
#include <random>


class RandomPointGenerator
{
public:
    RandomPointGenerator(int width, int height, int block_size_offset);
    ~RandomPointGenerator();
    int GetRandomWidth();
    int GetRandomHeight();
private:
    std::random_device m_random_seed;
    std::mt19937 m_random_generator;
    std::uniform_int_distribution<> m_random_width_range;
    std::uniform_int_distribution<> m_random_height_range;
};

#endif /* __RANDOM_GENERATOR__*/