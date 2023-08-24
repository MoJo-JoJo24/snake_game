#include "scoremanager.hpp"

ScoreManager::ScoreManager(): m_db(), m_top_scores(), m_number_of_top_scorers(5) 
{}

ScoreManager::~ScoreManager()
{
    m_top_scores.clear();
}

void ScoreManager::UpdateScoreTable(std::string &name, int score)
{
    ROW line;
    line.date = ScoreDataBase::CurrentDateNTime();
    line.name = name;
    line.score = std::to_string(score);
    m_db.WriteToDB(line);

    if (m_top_scores.empty())
    {
        UpdateTopScores();
    }
    else
    {
        auto iter = m_top_scores.begin();
        ++iter;
        int is_updated = 0;
        while (!is_updated && iter != m_top_scores.end())
        {
            size_t position = (*iter)[1].find(",");
            std::string str((*iter)[1].substr(0, position));
            
            int top_score = std::stoi(str);
            
            if (score > top_score)
            {
                std::string new_score = m_db.ReadFromDB(m_db.GetRowCount());
                ROW new_score_line = m_db.FromBuffer((char *)new_score.c_str());
                std::vector<std::string> new_top_score;
                new_top_score.push_back(new_score_line.name);
                new_top_score.push_back(new_score_line.score);
                new_top_score.push_back(new_score_line.date);
                m_top_scores.insert(iter, new_top_score);
                is_updated = 1;
            }
            ++iter;
        }

        if ((size_t)m_number_of_top_scorers + 1 < m_top_scores.size())
        {
            m_top_scores.erase(m_top_scores.end() - 1);
        }
    }
}

void ScoreManager::UpdateTopScores()
{
    std::multimap<int, ROW, std::greater<int>> scores;
    std::vector<ROW> vec = m_db.GETScoreTable();
    for (ROW row : vec)
    {
        scores.insert(std::pair<int, ROW>(std::stoi(row.score), row));
    }

    size_t range = m_number_of_top_scorers;
    range = scores.size() < range ? scores.size() : range;

    auto iter = scores.begin();
    std::string header_tmp = m_db.ReadFromDB(1).c_str();
    ROW header = m_db.FromBuffer(const_cast<char *>(header_tmp.c_str()));

    m_top_scores.push_back(std::vector<std::string>());
    m_top_scores[0].push_back(header.name);
    m_top_scores[0].push_back(header.score);
    m_top_scores[0].push_back(header.date);

    for (size_t i = 0; i < range; ++i)
    {
        m_top_scores.push_back(std::vector<std::string>());
        m_top_scores[i + 1].push_back(iter->second.name);
        m_top_scores[i + 1].push_back(iter->second.score);
        m_top_scores[i + 1].push_back(iter->second.date);
        ++iter;
    }        
}

std::vector<std::vector<std::string>> &ScoreManager::GetTopScores()
{
    return m_top_scores;
}