#ifndef __SCOREENGINE__
#define __SCOREENGINE__
#include <map>
#include "score_database.hpp"

const int number_of_final_score_rows = 5;

class ScoreManager
{
public:
    ScoreManager();
    ~ScoreManager();
    ScoreManager(const ScoreManager& other) = delete;
    const ScoreManager& operator=(const ScoreManager& other) = delete;

    std::vector<std::vector<std::string>> UpdateScoreTable(std::string &name, int score);
private:
    ScoreDataBase m_db;
    std::vector<ROW> m_scores; //GetScoreTable one updated
};

#endif /* __SCOREENGINE__ */