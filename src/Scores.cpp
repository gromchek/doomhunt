#include <fstream>
#include <algorithm>

#include "Common.h"
#include "Scores.h"


void Leaderboard::defaultRecords()
{
	records.push_back( { "JCMK", 66666 } );
	records.push_back( { "JRMR", 66666 } );
	records.push_back( { "Player", 0 } );
}

unsigned long Leaderboard::CalculateHash( const ScoreRecords &recs ) const
{
	std::string str;

	for( const auto &rec : recs )
	{
		str.append( { rec.name + std::to_string( rec.score ) } );
	}

	return HashString( str );
}

ScoreRecord Leaderboard::parseRecord( const std::string &str ) const
{
	const auto pos = str.find( ' ', 0 );

	return { str.substr( 0, pos ), std::stoul( str.substr( pos + 1 ) ) };
}

void Leaderboard::Init()
{
	records.reserve( 3 );

	ReadFile( scoreFile );

	score = 0;
}

void Leaderboard::UpdateRecords()
{
	for( auto &record : records )
	{
		if( record.name == "Player" )
		{
			const auto lastRecord = record.score;

			if( score > lastRecord )
			{
				record.score = score;
			}

			break;
		}
	}

	std::sort( records.begin(), records.end(),
			   []( const ScoreRecord &a, const ScoreRecord &b ) { return a.score > b.score; } );
}

void Leaderboard::ReadFile( const std::string &fileName )
{
	std::ifstream file( baseDir + fileName );

	if( !file )
	{
		defaultRecords();
		return;
	}

	unsigned long hash = 0;
	for( std::string str; std::getline( file, str, '\n' ); )
	{
		if( !isNumber( str ) )
		{
			defaultRecords();
			return;
		}

		hash = std::stoul( str );
		break;
	}

	ScoreRecords recs;
	recs.reserve( 3 );

	for( std::string str; std::getline( file, str, '\n' ); )
	{
		recs.push_back( parseRecord( str ) );
	}

	if( hash != CalculateHash( recs ) )
	{
		defaultRecords();
	}
	else
	{
		records = recs;
	}
}

void Leaderboard::WriteFile( const std::string &fileName ) const
{
	std::ofstream file( baseDir + fileName );

	if( !file )
	{
		return;
	}

	file << CalculateHash( records ) << '\n';

	for( const auto &record : records )
	{
		file << record.name << ' ' << record.score << '\n';
	}
}
