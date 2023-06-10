#include <cstddef>
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
    
private:
        

public:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        //clear screen
        FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::Pixel(0, 0, 0));

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
