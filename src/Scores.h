#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <vector>
#include <string>

const unsigned int SCORE_INCREMENT = 100;

struct ScoreRecord
{
	std::string name;
	unsigned int score;
};

using ScoreRecords = std::vector<ScoreRecord>;

class Leaderboard
{
private:
	ScoreRecords records;

	void defaultRecords();

	unsigned long CalculateHash( const ScoreRecords &recs ) const;
	ScoreRecord parseRecord( const std::string &str ) const;

	unsigned int score;

public:
	Leaderboard() = default;
	~Leaderboard() = default;

	void Init();

	void Reset();

	void UpdateRecords();

	unsigned int GetScores() const;
	void AddScores();

	const ScoreRecords &GetRecords() const;

	void ReadFile( const std::string &fileName );
	void WriteFile( const std::string &fileName ) const;
};

inline void Leaderboard::Reset()
{
	UpdateRecords();
	score = 0;
}

inline unsigned int Leaderboard::GetScores() const
{
	return score;
}

inline void Leaderboard::AddScores()
{
	score += SCORE_INCREMENT;
}

inline const ScoreRecords &Leaderboard::GetRecords() const
{
	return records;
}

#endif // HIGHSCORE_H
