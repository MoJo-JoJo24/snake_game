#include "scoremanager.hpp"

ScoreManager::ScoreManager(): m_db(), m_scores() 
{}

ScoreManager::~ScoreManager()
{}

std::vector<std::vector<std::string>> ScoreManager::UpdateScoreTable(std::string &name, int score)
{
    ROW line;
    line.date = ScoreDataBase::CurrentDateNTime();
    line.name = name;
    line.score = std::to_string(score);
    m_db.WriteToDB(line);

    std::multimap<int, ROW, std::greater<int>> scores;
    std::vector<ROW> vec = m_db.GETScoreTable();
    for (ROW row : vec)
    {
        scores.insert(std::pair(std::stoi(row.score), row));
    }

    size_t range = number_of_final_score_rows;
    range = scores.size() < range ? scores.size() : range;
    auto iter = scores.begin();
    std::vector<std::vector<std::string>> finalists(range + 1);
    std::string header_tmp = m_db.ReadFromDB(1).c_str();
    ROW header = m_db.FromBuffer(const_cast<char *>(header_tmp.c_str()));

    finalists[0].push_back(header.name);
    finalists[0].push_back(header.score);
    finalists[0].push_back(header.date);

    for (size_t i = 0; i < range; ++i)
    {
        finalists[i + 1].push_back(iter->second.name);
        finalists[i + 1].push_back(iter->second.score);
        finalists[i + 1].push_back(iter->second.date);
        ++iter;
    }

    return finalists;
}
