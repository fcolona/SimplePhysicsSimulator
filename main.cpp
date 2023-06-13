#include <cmath>
#include <cstddef>
#include <memory>
#include <vector>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

struct sObject
{
    float x;
    float y;
    float velocityX;
    float velocityY;
    float accelerationX;
    float accelerationY;
    olc::Pixel color;
    
    void updateKinematicAttributes(float fElapsedTime)
    {
        this->velocityX += this->accelerationX * fElapsedTime;
        this->velocityY += this->accelerationY * fElapsedTime;
            
        this->x += this->velocityX * fElapsedTime;
        this->y += -this->velocityY * fElapsedTime;
    }
            
    virtual void draw(olc::PixelGameEngine* engine) = 0;
    virtual void checkAndResolveCollision(olc::PixelGameEngine* engine) = 0;
};
struct sSquare : public sObject
{
    float sideLenght;
    sSquare(float x, float y, float velocityX, float velocityY,  float sideLenght, olc::Pixel color)
    {
        this->x = x;
        this->y = y;
            
        this->velocityX = velocityX;
        this->velocityY = velocityY;

        this->accelerationX = 0;
        this->accelerationY = 0;

        this->sideLenght = sideLenght;
        this->color = color;
    }
    sSquare(float x, float y, float velocityX, float velocityY, float accelerationX, float accelerationY,  float sideLenght, olc::Pixel color)
    {
        this->x = x;
        this->y = y;
            
        this->velocityX = velocityX;
        this->velocityY = velocityY;
        this->accelerationX = accelerationX;
        this->accelerationY = accelerationY;
        this->sideLenght = sideLenght;
        this->color = color;
    }
    void draw(olc::PixelGameEngine *engine) override
    {
            for(int x = 0; x < this->sideLenght; x++)
            {
                for(int y = 0; y < this->sideLenght; y++)
                {
                    engine->Draw(this->x + x, this->y + y, this->color);
                }
            };
        }
    void checkAndResolveCollision(olc::PixelGameEngine *engine) override
    {
        //Checks if it hits the right or left wall 
        if (this->x + sideLenght > engine->ScreenWidth() || this->x - sideLenght/2 < -10)
        {
            //Flip the sign of the horizontal component of the velocity
            this->velocityX = -this->velocityX;
        }
        //Checks if it hits the down or up wall
        else if (this->y + sideLenght > engine->ScreenHeight() || this->y - sideLenght/2 < 10)
        {
            //Flip the sign of the vertical component of the velocity
            this->velocityY = -this->velocityY;
        }
    }
};


struct sCircle : public sObject
{
    float radius;
    sCircle(float x, float y, float velocityX, float velocityY,  float radius, olc::Pixel color)
    {
        this->x = x;
        this->y = y;
            
        this->velocityX = velocityX;
        this->velocityY = velocityY;

        this->accelerationX = 0;
        this->accelerationY = 0;

        this->radius = radius;
        this->color = color;
    }
    sCircle(float x, float y, float velocityX, float velocityY, float accelerationX, float accelerationY,  float radius, olc::Pixel color)
    {
        this->x = x;
        this->y = y;
            
        this->velocityX = velocityX;
        this->velocityY = velocityY;
        this->accelerationX = accelerationX;
        this->accelerationY = accelerationY;
        this->radius = radius;
        this->color = color;
    }
    void draw(olc::PixelGameEngine *engine) override
    {
        engine->FillCircle(this->x, this->y, this->radius, this->color);
    }
    void checkAndResolveCollision(olc::PixelGameEngine *engine) override
    {
        //Checks if it hits the right or left wall 
        if (this->x + this->radius > engine->ScreenWidth() || this->x - radius < 0)
        {
            //Flip the sign of the horizontal component of the velocity
            this->velocityX = -this->velocityX;
        }
        //Checks if it hits the down or up wall
        else if (this->y + this->radius > engine->ScreenHeight() || this->y - this->radius < 1)
        {
            //Flip the sign of the vertical component of the velocity
            this->velocityY = -this->velocityY;
        }
    }
};

class Animation : public olc::PixelGameEngine
{
        
public:
	Animation()
	{
		// Name your application
		sAppName = "Animation";
	}

private:
    std::vector<sObject*> vecSpaceObjects;
    
public:
    	bool OnUserCreate() override
	{
        //Oblique Throw
        //sSquare* square = new sSquare(20.0f, 125.0f, 100, 100, 0, -125, 16.0f, olc::RED);
        sCircle* circle = new sCircle(20.0f, 125.0f, 100, 100, 0, -125, 15.0f, olc::RED);
        vecSpaceObjects.push_back(circle);
        
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
            
        //Draw objects
        for (auto object : vecSpaceObjects)
        {
            object->updateKinematicAttributes(fElapsedTime);
            object->checkAndResolveCollision(this);
            object->draw(this);
        }
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