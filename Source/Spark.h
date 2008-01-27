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

__private_extern__ void UpdateSparkColour(Spark *s);
__private_extern__ void InitSpark(Spark *s);
__private_extern__ void UpdateSpark(Spark *s);
__private_extern__ void DrawSpark(Spark *s);

#endif // !defined(SPARK_H)
