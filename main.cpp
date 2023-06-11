#include <cmath>
#include <cstddef>
#include <memory>
#include <vector>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
using namespace std;

// Override base class with your custom functionality

class Animation : public olc::PixelGameEngine
{
        
public:
	Animation()
	{
		// Name your application
		sAppName = "Animation";
	}
enum eShapes
    {
        SQUARE,
        CIRCLE
    };

    struct sObject
    {
        float x;
        float y;
        float velocityX;
        float velocityY;
        float accelerationX;
        float accelerationY;
        eShapes shape;
        int size;
            
        //Uniform Motion 
        sObject(float x, float y, float velocityX, float velocityY, eShapes shape, int size)
        {
            this->x = x;
            this->y = y;
            
            this->velocityX = velocityX;
            this->velocityY = velocityY;

            this->accelerationX = 0;
            this->accelerationY = 0;

            this->shape = shape;
            this->size = size;
        };
            
        //Accelerated Motion
        sObject(float x, float y, float velocityX, float velocityY, float accelerationX, float accelerationY, eShapes shape, int size) 
        {
            this->x = x;
            this->y = y;
            
            this->velocityX = velocityX;
            this->velocityY = velocityY;
            this->accelerationX = accelerationX;
            this->accelerationY = accelerationY;
            this->shape = shape;
            this->size = size;
        }
    };
private:
        
    vector<sObject> vecSpaceObjects;
    
    void resolveCollision(sObject& object)
    {
        if(object.shape == 0)
        {
            //Checks if it hits the left or righ wall 
           if (object.x + sqrt(object.size)/2 > ScreenWidth() || object.x - sqrt(object.size)/2 < 0 )
           {
               //Flip the sign of the horizontal component of the velocity
                object.velocityX = -object.velocityX;
           }
           //Checks if it hits the up or down wall
           else if (object.y + sqrt(object.size)/2 > ScreenHeight() || object.y - sqrt(object.size)/2 < 0)
           {
               //Flip the sign of the vertical component of the velocity
                object.velocityY = -object.velocityY;
           }
        }
    }
        
    void drawObjects(float fElapsedTime)
    {
        for (auto &object : vecSpaceObjects)
        {
            object.velocityX += object.accelerationX * fElapsedTime;
            object.velocityY += object.accelerationY * fElapsedTime;
            
            object.x += object.velocityX * fElapsedTime;
            object.y += -object.velocityY * fElapsedTime;

            //If it is a square
            if(object.shape == 0)
            {
                resolveCollision(object);

                for(int x = 0; x < object.size; x++)
                {
                    for(int y = 0; y < object.size; y++)
                    {
                        Draw(object.x + x, object.y + y, olc::WHITE);
                    }
                };
            }
            //If it is a circle
            else if(object.shape)
            {
                FillCircle(object.x, object.y, object.size, olc::WHITE);
            }
        };
    }

public:
	bool OnUserCreate() override
	{
        //Oblique Throw
        sObject square = sObject(20.0f, 125.0f, 100, 100, 0, -100, eShapes(0), (int) 16);
        vecSpaceObjects.push_back(square);
        
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        //clear screen
        FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::Pixel(0, 0, 0));
        //Draw Borders
        DrawLine(1, 1, ScreenWidth() - 1, 1, olc::BLUE);
	    DrawLine(1, 1, 1, ScreenHeight(), olc::BLUE);
	    DrawLine(ScreenWidth() - 1, 1, ScreenWidth() - 1, ScreenHeight(), olc::BLUE);
	    DrawLine(1, ScreenHeight() - 1, ScreenWidth() - 1, ScreenHeight() - 1, olc::BLUE);
        drawObjects(fElapsedTime);

        return true;
	}
};

int main()
{
	Animation demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}	