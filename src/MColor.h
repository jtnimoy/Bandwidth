#ifndef _MColor_H_
#define _MColor_H_

#include "ofMain.h"

using namespace std;


class MColor{


	public:

		MColor();
		MColor(unsigned int rgb);
		MColor(float $red, float $green, float $blue);
		MColor(float $red, float $green, float $blue, float $alpha);

		MColor(float, float, float, const char* mode);
		MColor(float, float ,float, float, const char* mode);

		~MColor();

		float alpha;

		// SETTERS
		void RGB_(float, float, float);
		void HSV(float, float, float);
		void red(float);
		void green(float);
		void blue(float);
		void hue(float);
		void sat(float);
		void val(float);
		void inc(int, float);
		void incRed(float);
		void incGreen(float);
		void incBlue(float);
		void incHue(float);
		void incSat(float);
		void incVal(float);

		// GETTERS
		float red();
		float green();
		float blue();
		float hue();
		float sat();
		float val();

		// TRANSFER + RELATIONSHIPS
		void copyFrom(MColor $color);
		void swap(MColor $color);
		MColor complement();
		MColor mixTo(MColor,float);
		void mixSelfTo(MColor,float);
	void lerpHueTo(MColor $dst, float $amt);

		// OPERATORS
		// These compare RGB.
		bool operator==(MColor);
		bool operator!=(MColor);
		// These compare brightness (value) only.
		bool operator<(MColor);
		bool operator>(MColor);
		bool operator<=(MColor);
		bool operator>=(MColor);
		MColor operator+(MColor);
		void operator+=(MColor);
		MColor operator-(MColor);
		void operator-=(MColor);
		MColor operator*(MColor);
		MColor operator*(float);
		void operator*=(MColor);
		MColor operator/(MColor);
		void operator/=(MColor);

		// CONVENIENCE
		void glColor(float $alpha);
		void glColor();
		void println();

	private:

		float _red;
		float _green;
		float _blue;
		float _hue;
		float _sat;
		float _val;

		void _normalizeRGB();
		void _normalizeHSV();

		void _updateHSV();
		void _updateRGB();

};

#endif
