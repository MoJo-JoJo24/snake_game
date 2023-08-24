#ifndef __SCOREENGINE__
#define __SCOREENGINE__
#include <map>
#include "score_database.hpp"

class ScoreManager
{
public:
    ScoreManager();
    ~ScoreManager();
    ScoreManager(const ScoreManager& other) = delete;
    const ScoreManager& operator=(const ScoreManager& other) = delete;

    void UpdateScoreTable(std::string &name, int score);
    std::vector<std::vector<std::string>> &GetTopScores();
private:
    void UpdateTopScores();
    ScoreDataBase m_db;
    std::vector<std::vector<std::string>> m_top_scores;
    int m_number_of_top_scorers;
};

#endif /* __SCOREENGINE__ */