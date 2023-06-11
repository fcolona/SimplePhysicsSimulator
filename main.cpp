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
                for(int x = 0; x < object.size; x++)
                {
                    for(int y = 0; y < object.size; y++)
                    {
                        Draw(object.x + x, object.y + y, olc::WHITE);
                    }
                };
            }
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
        sObject square = sObject(0.0f, 235.0f, 125, 125, 0, -115, eShapes(1), (int) 16);
        vecSpaceObjects.push_back(square);
        
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        //clear screen
        FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::Pixel(0, 0, 0));
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