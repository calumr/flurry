// Spark.h: interface for the Spark class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(SPARK_H)
#define SPARK_H

typedef struct Spark  
{
    float position[3];
    int mystery;
    float delta[3];
    float color[4];    
} Spark;

void UpdateSparkColour(Spark *s);
void InitSpark(Spark *s);
void UpdateSpark(Spark *s);
void DrawSpark(Spark *s);

#endif // !defined(SPARK_H)
