// Star.h: interface for the Star class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(STAR_H)
#define STAR_H

typedef struct Star {
    float position[3];
    bool ate;
    float mystery;
    float rotSpeed;
} Star;

void UpdateStar(Star* s);
void InitStar(Star* s);

#endif  // !defined(STAR_H)
