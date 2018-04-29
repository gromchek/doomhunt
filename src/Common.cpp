#include <algorithm>
#include "Common.h"

//djb2
unsigned long HashString( const std::string &str )
{
	unsigned long hash = 5381;

	for( auto c : str )
	{
		hash = ( ( hash << 5 ) + hash ) + c; /* hash * 33 + c */
	}

	return hash;
}

bool isNumber( const std::string &str )
{
	return !str.empty() && std::all_of( str.begin(), str.end(), isdigit );
}
