// Star.h: interface for the Star class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(STAR_H)
#define STAR_H

typedef struct Star  
{
	float position[3];
	bool ate;
	float mystery;
	float rotSpeed;
} Star;

__private_extern__ void UpdateStar(Star *s);
__private_extern__ void DrawStar(Star *s);
__private_extern__ void InitStar(Star *s);

#endif // !defined(STAR_H)
