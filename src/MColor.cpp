/**
   I love Keith Pasko
 */

#include "MColor.h"
#include <iostream>
//#define PI 3.141592

using namespace std;

/////////////////////////////////////////////
// PUBLIC
////////////////////////////////////////////
MColor::MColor(){
	_red = 0;
	_green = 0;
	_blue = 0;
	_hue = 0;
	_sat = 0;
	_val = 0;
	alpha=1;
}

MColor::MColor(unsigned int rgb){
	_red = (rgb >> 16) / 255.0;
	_green = (0xFF & (rgb >> 8)) / 255.0;
	_blue = (0xFF & rgb) / 255.0;
	_hue = 0;
	_sat = 0;
	_val = 0;
	_updateHSV();
	alpha=1;
}


MColor::MColor(float $red, float $green, float $blue){
	_red = $red;
	_green = $green;
	_blue = $blue;
	_hue = 0;
	_sat = 0;
	_val = 0;
	_updateHSV();
	alpha=1;
}

MColor::MColor(float $red, float $green, float $blue, float $alpha){
	alpha=$alpha;
	_red = $red;
	_green = $green;
	_blue = $blue;
	_hue = 0;
	_sat = 0;
	_val = 0;
	_updateHSV();
}

MColor::~MColor(){}


MColor::MColor(float $xx, float $yy, float $zz, const char* _mode){
	const char* mode="RGB";
	if (_mode==mode) {
		_red = $xx;
		_green = $yy;
		_blue = $zz;
		_hue = 0;
		_sat = 0;
		_val = 0;
		_updateHSV();
	}else{
		_red=0;
		_green=0;
		_blue=0;
		_hue=$xx;
		_sat=$yy;
		_val=$zz;
		_updateRGB();
	}
}

MColor::MColor(float $xx, float $yy, float $zz, float $alpha, const char* _mode){
	alpha=$alpha;
	const char* mode="RGB";
	if (_mode==mode) {
		_red = $xx;
		_green = $yy;
		_blue = $zz;
		_hue = 0;
		_sat = 0;
		_val = 0;
		_updateHSV();
	}else{
		_red=0;
		_green=0;
		_blue=0;
		_hue=$xx;
		_sat=$yy;
		_val=$zz;
		_updateRGB();
	}
}


/////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////
float MColor::red(){
	return _red;
}
float MColor::green(){
	return _green;
}
float MColor::blue(){
	return _blue;
}

float MColor::hue(){
	return _hue;
}
float MColor::sat(){
	return _sat;
}
float MColor::val(){
	return _val;
}


/////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////
void MColor::RGB_(float $r, float $g, float $b){
	_red = $r;
	_green = $g;
	_blue = $b;
	_updateHSV();
}

void MColor::HSV(float $h, float $s, float $v){
	_hue = $h;
	_sat = $s;
	_val = $v;
	_updateRGB();
}

void MColor::red(float $num){
	_red = $num;
	_updateHSV();
}

void MColor::green(float $num){
	_green = $num;
	_updateHSV();
}

void MColor::blue(float $num){
	_blue = $num;
	_updateHSV();
}

void MColor::hue(float $num){
	_hue = $num;
	_updateRGB();
}

void MColor::sat(float $num){
	_val = $num;
	_updateRGB();
}

void MColor::val(float $num){
	_sat = $num;
	_updateRGB();
}

void MColor::inc(int $channel, float $amount){
	switch($channel){
		case 0:
			incRed($amount);
			break;
		case 1:
			incGreen($amount);
			break;
		case 2:
			incBlue($amount);
			break;
		case 3:
			incHue($amount);
			break;
		case 4:
			incSat($amount);
			break;
		case 5:
			incVal($amount);
			break;
		default:
			cout << "Invalid $channel value passed to MColor::inc(int $channel, float $amount) - 012345:RGBHSV" << endl;
	}
}
void MColor::incRed(float $num){
	_red += $num;
	_updateHSV();
}
void MColor::incGreen(float $num){
	_green += $num;
	_updateHSV();
}
void MColor::incBlue(float $num){
	_blue += $num;
	_updateHSV();
}
void MColor::incHue(float $num){
	_hue += $num;
	_updateRGB();
}
void MColor::incSat(float $num){
	_sat += $num;
	_updateRGB();
}
void MColor::incVal(float $num){
	_val += $num;
	_updateRGB();
}

/////////////////////////////////////////////
// COLOR TRANSFER AND RELATIONS
////////////////////////////////////////////
void MColor::copyFrom(MColor $color){
	//RGB($color.red(), $color.green(), $color.blue());
	_red = $color.red();
	_green = $color.green();
	_blue = $color.blue();
	alpha = $color.alpha;
	_updateHSV();
}
void MColor::swap(MColor $color){
	float tr, tg, tb;
	tr = _red;
	tg = _green;
	tb = _blue;
	RGB_($color.red(), $color.green(), $color.blue());
	$color.RGB_(tr, tg, tb);
}
MColor MColor::complement(){
	MColor temp;
	temp.copyFrom(*this);
	temp._hue+=3.141592;
	temp._updateRGB();
	return temp;
}
MColor MColor::mixTo(MColor c, float amt){
	MColor temp;
	//temp.copyFrom((*this)+(c-(*this))*mixVal);
	//temp.copyFrom(*this+(c-*this)*amt);
	temp._red+=(c.red()-temp._red)*amt;
	temp._green+=(c.green()-temp._green)*amt;
	temp._blue+=(c.blue()-temp._blue)*amt;
	return temp;
}

void MColor::mixSelfTo(MColor c, float amt){
	//this->copyFrom((*this)+(c-(*this))*mixVal);
	//this->copyFrom(*this+(c-*this)*amt);
	this->_red+=(c.red()-this->_red)*amt;
	this->_green+=(c.green()-this->_green)*amt;
	this->_blue+=(c.blue()-this->_blue)*amt;
}

void MColor::lerpHueTo(MColor $dst, float $amt){
	float diff = $dst.hue() - hue();
	if(diff > PI) diff = (PI * 2 - diff) * -1;
	else if(diff < -PI) diff = PI * 2 + diff;
	float hueChange = diff * $amt;
	hue(hue() + hueChange);
}

/////////////////////////////////////////////
// OPERATORS
////////////////////////////////////////////
bool MColor::operator!=(MColor $color){
	if(_red!=$color.red() && _green!=$color.green() && _blue!=$color.blue()) return true;
  return false;
}
bool MColor::operator==(MColor $color){
	if(_red==$color.red() && _green==$color.green() && _blue==$color.blue()) return true;
  return false;
}
bool MColor::operator<(MColor $color){
	if(_val<$color.val()) return true;
  return false;
}
bool MColor::operator>(MColor $color){
	if(_val>$color.val()) return true;
  return false;
}
bool MColor::operator<=(MColor $color){
	if(_val<=$color.val()) return true;
  return false;
}
bool MColor::operator>=(MColor $color){
	if(_val>=$color.val()) return true;
  return false;
}
MColor MColor::operator+(MColor p){
	MColor temp;
	temp.copyFrom(*this);
	temp.RGB_(temp.red() + p.red(), temp.green() + p.green(), temp.blue() + p.blue());
	return temp;
}
void MColor::operator+=(MColor p){
	RGB_(this->red() + p.red(), this->green() + p.green(), this->blue() + p.blue());
}
MColor MColor::operator-(MColor p){
	MColor temp;
	temp.copyFrom(*this);
	temp.RGB_(temp.red() - p.red(), temp.green() - p.green(), temp.blue() - p.blue());
	return temp;
}
void MColor::operator-=(MColor p){
	RGB_(this->red() - p.red(), this->green() - p.green(), this->blue() - p.blue());
}
MColor MColor::operator*(MColor p){
	MColor temp;
	temp.copyFrom(*this);
	temp.RGB_(temp.red() * p.red(), temp.green() * p.green(), temp.blue() * p.blue());
	return temp;
}
MColor MColor::operator*(float p){
	MColor temp;
	temp.copyFrom(*this);
	temp.RGB_(temp.red() * p, temp.green() * p, temp.blue() * p);
	temp._normalizeRGB();
	return temp;
}
void MColor::operator*=(MColor p){
	RGB_(this->red() * p.red(), this->green() * p.green(), this->blue() * p.blue());
}
MColor MColor::operator/(MColor p){
	MColor temp;
	temp.copyFrom(*this);
	temp.RGB_(temp.red() / p.red(), temp.green() / p.green(), temp.blue() / p.blue());
	return temp;
}
void MColor::operator/=(MColor p){
	RGB_(this->red() / p.red(), this->green() / p.green(), this->blue() / p.blue());
}

/////////////////////////////////////////////
// CONVENIENCE
////////////////////////////////////////////
void MColor::glColor(float $alpha){
	glColor4f(_red, _green, _blue, $alpha);
}

void MColor::glColor(){
	glColor4f(_red,_green,_blue,alpha);
}

void MColor::println(){
	cout << "MColor :: RGB(" << _red << ", " << _green << ", " << _blue << ") : HSV(" << _hue << ", " << _sat << ", "<< _val << ")" << endl;
}

/////////////////////////////////////////////
// PRIVATE
////////////////////////////////////////////
void MColor::_normalizeRGB(){
	if(_red > 1) _red = 1;
	else if(_red < 0) _red = 0;
	if(_green > 1) _green = 1;
	else if(_green < 0) _green = 0;
	if(_blue > 1) _blue = 1;
	else if(_blue < 0) _blue = 0;
}
void MColor::_normalizeHSV(){
	while(_hue>2*3.141592) _hue-=2*3.141592;
	while(_hue<0) _hue+=2*3.141592;
	if(_sat > 1) _sat = 1;
	else if(_sat < 0) _sat = 0;
	if(_val > 1) _val = 1;
	else if(_val < 0) _val = 0;
}

//color transform functions adapted from http://en.wikipedia.org/wiki/HSV_color_space

// Set _HSVData, after updating _RGBData.
void MColor::_updateHSV(){

	_normalizeRGB();

	float r, g, b;
	r = _red;
	g = _green;
	b = _blue;

	float h, s, v;
	h = 0;
	s = 0;
	v = 0;

	float my_min=fmin(fmin(r,g),b);
	float my_max=fmax(fmax(r,g),b);
	v=my_max;
	float diff=v-my_min;

//	if (my_max==my_min) cout << "hue is undefined" << endl;



	if (r==my_max && g>=b){
		h=(3.141592/3.0)*(g-b)/diff;
	}else if(r==my_max && g<b){
		h=(3.141592/3.0)*(g-b)/diff+2*3.141592;
	}else if(g==my_max){
		h=(3.141592/3.0)*(b-r)/diff+(2*3.141592/3.0);
	}else	if(b==my_max){
		h=(3.141592/3.0)*(r-g)/diff+(4*3.141592/3.0);
	}


	if (my_max==0) s=0; else s=1-(my_min/my_max);

		if (my_max==my_min) h = 0;
	_hue=h;
	_sat=s;
	_val=v;
	_normalizeHSV();
}

void MColor::_updateRGB(){

	_normalizeHSV();

	float h, s, v;
	h = _hue;
	s = _sat;
	v = _val;

	float r, g, b, htemp;
	r = 0;
	g = 0;
	b = 0;
	htemp = 0;

	if (h==M_2_PI) htemp=0; else htemp=h;
	htemp=htemp*180.0/3.141592;
	htemp=htemp/60.0;
	int i=floor(htemp);
	float ftemp=htemp-i;

	float val1=v*(1.0-s);
	float val2=v*(1.0-(s*ftemp));
	float val3=v*(1.0-(s*(1.0-ftemp)));

	switch(i){
		case 0: {
			r = v; g = val3 ; b = val1;
		}break;
		case 1: {
			r = val2 ; g = v ; b = val1;
		}break;
		case 2: {
			r = val1 ; g = v ; b = val3;
		}break;
		case 3: {
			r = val1 ; g = val2 ; b = v;
		}break;
		case 4: {
			r = val3 ; g = val1 ; b = v;
		}break;
		case 5:{
			r = v; g = val1 ; b = val2;
		}break;
		default: break;
	}

	_red=r;
	_green=g;
	_blue=b;
	_normalizeRGB();
}




