//----------------------------------------------------------
//
// Code generated with Faust 0.9.73 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline float faustpower(float x)          { return powf(x,N); } 
template <int N> inline double faustpower(double x)        { return pow(x,N); }
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
#endif
/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections :
	the ARCHITECTURE section (in two parts) and the USER section. Each section
	is governed by its own copyright and license. Please check individually
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2004-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either version 3
	of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

	EXCEPTION : As a special exception, you may create a larger work
	that contains this FAUST architecture section and distribute
	that work under terms of your choice, so long as this FAUST
	architecture section is not modified.

	MAX MSP SDK : in order to compile a MaxMSP external with this
	architecture file you will need the official MaxMSP SDK from
	cycling'74. Please check the corresponding license.

 ************************************************************************
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>

#ifdef __APPLE__
#include <Carbon/Carbon.h>
#include <unistd.h>
#endif

#ifdef WIN32
#ifndef NAN
    static const unsigned long __nan[2] = {0xffffffff, 0x7fffffff};
    #define NAN (*(const float *) __nan)
#endif
#endif

#define FAUSTFLOAT double

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/
 
#ifndef FAUST_UI_H
#define FAUST_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust User Interface
 * This abstract class contains only the method that the faust compiler can
 * generate to describe a DSP interface.
 ******************************************************************************/

class UI
{

    public:

        UI() {}

        virtual ~UI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    protected:
    
        UI* fUI;

    public:
    
        DecoratorUI(UI* ui = 0):fUI(ui)
        {}

        virtual ~DecoratorUI() { delete fUI; }

        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }

        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
            { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
            { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
            { fUI->addNumEntry(label, zone, init, min, max, step); }

        // -- passive widgets	
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
            { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            { fUI->addVerticalBargraph(label, zone, min, max); }

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }

};

#endif
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/
 
#ifndef FAUST_JSONUI_H
#define FAUST_JSONUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
};

#endif  // FAUST_PATHBUILDER_H
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __meta__
#define __meta__

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
    virtual ~Meta() {};
};

#endif


#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <assert.h>

/*******************************************************************************
 * JSONUI : Faust User Interface
 * This class produce a complete JSON decription of the DSP instance.
 ******************************************************************************/

class JSONUI : public PathBuilder, public Meta, public UI
{

    protected:
    
        std::stringstream fJSON;
        std::stringstream fUI;
        std::stringstream fMeta;
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        std::string fName;
        std::string fExpandedCode;
        std::string fSHAKey;
    
        char fCloseUIPar;
        char fCloseMetaPar;
        int fTab;
    
        int fInputs, fOutputs;
         
        void tab(int n, std::ostream& fout)
        {
            fout << '\n';
            while (n-- > 0) {
                fout << '\t';
            }
        }
    
        void addMeta(int tab_val, bool quote = true)
        {
            if (fMetaAux.size() > 0) {
                tab(tab_val, fUI); fUI << "\"meta\": [";
                std::string sep = "";
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    fUI << sep;
                    tab(tab_val + 1, fUI); fUI << "{ \"" << fMetaAux[i].first << "\": \"" << fMetaAux[i].second << "\" }";
                    sep = ",";
                }
                tab(tab_val, fUI); fUI << ((quote) ? "],": "]");
                fMetaAux.clear();
            }
        }
        
        void init(const std::string& name, int inputs, int outputs, const std::string& sha_key, const std::string& dsp_code)
        {
            fTab = 1;
            
            // Start Meta generation
            tab(fTab, fMeta); fMeta << "\"meta\": [";
            fCloseMetaPar = ' ';
            
            // Start UI generation
            tab(fTab, fUI); fUI << "\"ui\": [";
            fCloseUIPar = ' ';
            fTab += 1;
            
            fName = name;
            fInputs = inputs;
            fOutputs = outputs;
            fExpandedCode = dsp_code;
            fSHAKey = sha_key;
        }
        
        inline std::string flatten(const std::string& src)
        {
            std::stringstream dst;
            for (size_t i = 0; i < src.size(); i++) {
                switch (src[i]) {
                    case '\n':
                    case '\t':
                        dst << ' ';
                        break;
                    case '"':
                        dst << "\\" << '"';
                        break;
                    default:
                        dst << src[i];
                        break;
                }
            }
            return dst.str();
        }
      
     public:
     
        JSONUI(const std::string& name, int inputs, int outputs, const std::string& sha_key, const std::string& dsp_code)
        {
            init(name, inputs, outputs, sha_key, dsp_code);
        }

        JSONUI(const std::string& name, int inputs, int outputs)
        {
            init(name, inputs, outputs, "", "");
        }

        JSONUI(int inputs, int outputs)
        {
            init("", inputs, outputs, "", "");
        }
        
        JSONUI()
        {
            init("", -1, -1, "", "");
        }
 
        virtual ~JSONUI() {}

        // -- widget's layouts
    
        virtual void openGenericGroup(const char* label, const char* name)
        {
            fControlsLevel.push_back(label);
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            addMeta(fTab + 1);
            tab(fTab, fUI); fUI << "\"items\": [";
            fCloseUIPar = ' ';
            fTab += 1;
        }

        virtual void openTabBox(const char* label)
        {
            openGenericGroup(label, "tgroup");
        }
    
        virtual void openHorizontalBox(const char* label)
        {
            openGenericGroup(label, "hgroup");
        }
    
        virtual void openVerticalBox(const char* label)
        {
            openGenericGroup(label, "vgroup");
        }
    
        virtual void closeBox()
        {
            fControlsLevel.pop_back();
            fTab -= 1;
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        // -- active widgets
    
        virtual void addGenericButton(const char* label, const char* name)
        {
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            tab(fTab + 1, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab + 1, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab + 1, fUI); fUI << "\"address\": \"" << buildPath(label) << "\"" << ((fMetaAux.size() > 0) ? "," : "");
            addMeta(fTab + 1, false);
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericButton(label, "button");
        }
    
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericButton(label, "checkbox");
        }

        virtual void addGenericEntry(const char* label, const char* name, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            tab(fTab + 1, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab + 1, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab + 1, fUI); fUI << "\"address\": \"" << buildPath(label) << "\"" << ",";
            addMeta(fTab + 1);
            tab(fTab + 1, fUI); fUI << "\"init\": \"" << init << "\",";
            tab(fTab + 1, fUI); fUI << "\"min\": \"" << min << "\",";
            tab(fTab + 1, fUI); fUI << "\"max\": \"" << max << "\",";
            tab(fTab + 1, fUI); fUI << "\"step\": \"" << step << "\"";
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericEntry(label, "vslider", init, min, max, step);
        }
    
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericEntry(label, "hslider", init, min, max, step);
        }
    
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericEntry(label, "nentry", init, min, max, step);
        }

        // -- passive widgets
    
        virtual void addGenericBargraph(const char* label, const char* name, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            tab(fTab + 1, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab + 1, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab + 1, fUI); fUI << "\"address\": \"" << buildPath(label) << "\"" << ",";
            addMeta(fTab + 1);
            tab(fTab + 1, fUI); fUI << "\"min\": \"" << min << "\",";
            tab(fTab + 1, fUI); fUI << "\"max\": \"" << max << "\"";
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            addGenericBargraph(label, "hbargraph", min, max);
        }
    
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addGenericBargraph(label, "vbargraph", min, max);
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            fMetaAux.push_back(std::make_pair(key, val));
        }
    
        // Meta interface
        virtual void declare(const char* key, const char* value)
        {
            fMeta << fCloseMetaPar;
            if ((strcmp(key, "name") == 0) && (fName == "")) fName = value;
            tab(fTab, fMeta); fMeta << "{ " << "\"" << key << "\"" << ": " << "\"" << value << "\" }";
            fCloseMetaPar = ',';
        }
    
        std::string JSON(bool flat = false)
        {
            fTab = 0;
            fJSON << "{";
            fTab += 1;
            tab(fTab, fJSON); fJSON << "\"name\": \"" << fName << "\",";
            if (fSHAKey != "") { tab(fTab, fJSON); fJSON << "\"sha_key\": \"" << fSHAKey << "\","; }
            if (fExpandedCode != "") { tab(fTab, fJSON); fJSON << "\"code\": \"" << fExpandedCode << "\","; }
            tab(fTab, fJSON); fJSON << "\"inputs\": \"" << fInputs << "\","; 
            tab(fTab, fJSON); fJSON << "\"outputs\": \"" << fOutputs << "\",";
            tab(fTab, fMeta); fMeta << "],";
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            if (fCloseMetaPar == ',') { // If "declare" has been called, fCloseMetaPar state is now ','
                fJSON << fMeta.str() << fUI.str();
            } else {
                fJSON << fUI.str();
            }
            tab(fTab, fJSON); fJSON << "}" << std::endl;
            return (flat) ? flatten(fJSON.str()) : fJSON.str();
        }
    
};

#endif // FAUST_JSONUI_H
/************************************************************************
    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

 ************************************************************************
 ************************************************************************/
 
/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

#ifndef __dsp__
#define __dsp__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;

//----------------------------------------------------------------
//  Signal processor definition
//----------------------------------------------------------------

class dsp {

    protected:

        int fSamplingFreq;

    public:

        dsp() {}
        virtual ~dsp() {}

        virtual int getNumInputs() 										= 0;
        virtual int getNumOutputs() 									= 0;
        virtual void buildUserInterface(UI* ui_interface) 				= 0;
        virtual void init(int samplingRate) 							= 0;
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 	= 0;
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = 0):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs()                          { return fDSP->getNumInputs(); }
        virtual int getNumOutputs()                         { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface)   { fDSP->buildUserInterface(ui_interface); }
        virtual void init(int samplingRate)                 { fDSP->init(samplingRate); }
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
       
};

//----------------------------------------------------------------
// On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
// flags to avoid costly denormals
//----------------------------------------------------------------

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <string.h>
#include <stdlib.h>


using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

inline int lsr(int x, int n)	{ return int(((unsigned int)x) >> n); }
inline int int2pow2(int x)		{ int r=0; while ((1<<r)<x) r++; return r; }

long lopt(char* argv[], const char* name, long def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

bool isopt(char* argv[], const char* name)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
	return false;
}

const char* lopts(char* argv[], const char* name, const char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}

#endif


using namespace std;

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/


/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
  private:
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	int 	iConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	FAUSTFLOAT 	fslider0;
	double 	fConst29;
	double 	fConst30;
	double 	fRec3[2];
	double 	fRec2[2];
	FAUSTFLOAT 	fslider1;
	double 	fConst31;
	double 	fConst32;
	double 	fRec1[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	double 	fRec6[2];
	double 	fRec5[2];
	FAUSTFLOAT 	fslider4;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider5;
	double 	fRec0[5];
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fRec7[5];
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
	double 	fConst81;
	double 	fConst82;
	double 	fRec8[5];
	double 	fConst83;
	double 	fConst84;
	double 	fConst85;
	double 	fConst86;
	double 	fConst87;
	double 	fConst88;
	double 	fConst89;
	double 	fConst90;
	double 	fConst91;
	double 	fConst92;
	double 	fConst93;
	double 	fConst94;
	double 	fConst95;
	double 	fConst96;
	double 	fConst97;
	double 	fConst98;
	double 	fConst99;
	double 	fConst100;
	double 	fConst101;
	double 	fConst102;
	double 	fConst103;
	double 	fConst104;
	double 	fConst105;
	double 	fConst106;
	double 	fConst107;
	double 	fRec9[5];
	double 	fConst108;
	double 	fConst109;
	double 	fConst110;
	double 	fConst111;
	double 	fConst112;
	double 	fConst113;
	double 	fConst114;
	double 	fConst115;
	double 	fConst116;
	double 	fConst117;
	double 	fConst118;
	double 	fConst119;
	double 	fConst120;
	double 	fConst121;
	double 	fConst122;
	double 	fConst123;
	double 	fConst124;
	double 	fConst125;
	double 	fConst126;
	double 	fConst127;
	double 	fConst128;
	double 	fConst129;
	double 	fConst130;
	double 	fConst131;
	double 	fConst132;
	double 	fRec10[5];
	double 	fConst133;
	double 	fConst134;
	double 	fConst135;
	double 	fConst136;
	double 	fConst137;
	double 	fConst138;
	double 	fConst139;
	double 	fConst140;
	double 	fConst141;
	double 	fConst142;
	double 	fConst143;
	double 	fConst144;
	double 	fConst145;
	double 	fConst146;
	double 	fConst147;
	double 	fConst148;
	double 	fConst149;
	double 	fConst150;
	double 	fConst151;
	double 	fConst152;
	double 	fConst153;
	double 	fConst154;
	double 	fConst155;
	double 	fConst156;
	double 	fConst157;
	double 	fRec11[5];
	double 	fConst158;
	double 	fConst159;
	double 	fConst160;
	double 	fConst161;
	double 	fConst162;
	double 	fConst163;
	double 	fConst164;
	double 	fConst165;
	double 	fConst166;
	double 	fConst167;
	double 	fConst168;
	double 	fConst169;
	double 	fConst170;
	double 	fConst171;
	double 	fConst172;
	double 	fConst173;
	double 	fConst174;
	double 	fConst175;
	double 	fConst176;
	double 	fConst177;
	double 	fConst178;
	double 	fConst179;
	double 	fConst180;
	double 	fConst181;
	double 	fConst182;
	double 	fRec12[5];
	double 	fConst183;
	double 	fConst184;
	double 	fConst185;
	double 	fConst186;
	double 	fConst187;
	double 	fConst188;
	double 	fConst189;
	double 	fConst190;
	double 	fConst191;
	double 	fConst192;
	double 	fConst193;
	double 	fConst194;
	double 	fConst195;
	double 	fConst196;
	double 	fConst197;
	double 	fConst198;
	double 	fConst199;
	double 	fConst200;
	double 	fConst201;
	double 	fConst202;
	double 	fConst203;
	double 	fConst204;
	double 	fConst205;
	double 	fConst206;
	double 	fConst207;
	double 	fRec13[5];
	double 	fConst208;
	double 	fConst209;
	double 	fRec14[5];
	double 	fRec15[5];
	double 	fRec16[5];
	double 	fRec17[5];
	double 	fRec18[5];
	double 	fRec19[5];
	double 	fRec20[5];
	double 	fRec21[5];
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("effect.lib/name", "Faust Audio Effect Library");
		m->declare("effect.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/copyright", "Julius O. Smith III");
		m->declare("effect.lib/version", "1.33");
		m->declare("effect.lib/license", "STK-4.3");
		m->declare("effect.lib/exciter_name", "Harmonic Exciter");
		m->declare("effect.lib/exciter_author", "Priyanka Shekar (pshekar@ccrma.stanford.edu)");
		m->declare("effect.lib/exciter_copyright", "Copyright (c) 2013 Priyanka Shekar");
		m->declare("effect.lib/exciter_version", "1.0");
		m->declare("effect.lib/exciter_license", "MIT License (MIT)");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/version", "1.29");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/version", "1.0");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/version", "1.0");
		m->declare("math.lib/license", "LGPL with exception");
	}

	virtual int getNumInputs() 	{ return 2; }
	virtual int getNumOutputs() 	{ return 16; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		iConst0 = min(192000, max(1, fSamplingFreq));
		fConst1 = double(iConst0);
		fConst2 = tan((628.3185307179587 / double(iConst0)));
		fConst3 = (iConst0 * fConst2);
		iConst4 = faustpower<2>(iConst0);
		fConst5 = sqrt((4.0 * ((iConst4 * fConst2) * tan((314.1592653589793 / double(iConst0))))));
		fConst6 = faustpower<2>(fConst5);
		fConst7 = ((2.0 * fConst3) - (0.5 * (fConst6 / fConst3)));
		fConst8 = (fConst7 / fConst1);
		fConst9 = (11.31370849898476 * fConst8);
		fConst10 = (2.82842712474619 * fConst7);
		fConst11 = (1.0 / fConst1);
		fConst12 = (fConst6 * fConst11);
		fConst13 = faustpower<2>(fConst7);
		fConst14 = (4 * fConst13);
		fConst15 = (fConst14 + (8 * fConst6));
		fConst16 = faustpower<2>(fConst11);
		fConst17 = ((16 + (fConst16 * (fConst15 + (fConst12 * (fConst12 - fConst10))))) - fConst9);
		fConst18 = (5.65685424949238 * fConst7);
		fConst19 = (4 * fConst12);
		fConst20 = faustpower<3>(fConst11);
		fConst21 = (fConst6 * fConst20);
		fConst22 = (22.62741699796952 * fConst8);
		fConst23 = ((fConst22 + (fConst21 * (fConst19 - fConst18))) - 64);
		fConst24 = ((fConst21 * (fConst18 + fConst19)) - (64 + fConst22));
		fConst25 = (8 * fConst13);
		fConst26 = (96 + (fConst16 * ((0 - ((16 * fConst6) + fConst25)) + (6 * (faustpower<4>(fConst5) * fConst16)))));
		fConst27 = (16 + ((fConst16 * (fConst15 + (fConst12 * (fConst12 + fConst10)))) + fConst9));
		fConst28 = (1.0 / fConst27);
		fslider0 = -3e+01;
		fConst29 = exp((0 - (5e+02 / double(iConst0))));
		fConst30 = exp((0 - (2.5 / double(iConst0))));
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		fslider1 = 5.0;
		fConst31 = exp((0 - (1e+03 / double(iConst0))));
		fConst32 = (1.0 - fConst31);
		for (int i=0; i<2; i++) fRec1[i] = 0;
		fslider2 = 1.0;
		fslider3 = -3e+01;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		fslider4 = 5.0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		fslider5 = 1.0;
		for (int i=0; i<5; i++) fRec0[i] = 0;
		fConst33 = (0 - fConst25);
		fConst34 = (fConst16 / fConst27);
		fConst35 = tan((1256.6370614359173 / double(iConst0)));
		fConst36 = (iConst0 * fConst35);
		fConst37 = sqrt((4.0 * ((iConst4 * fConst35) * fConst2)));
		fConst38 = faustpower<2>(fConst37);
		fConst39 = ((2.0 * fConst36) - (0.5 * (fConst38 / fConst36)));
		fConst40 = (fConst39 / fConst1);
		fConst41 = (11.31370849898476 * fConst40);
		fConst42 = (2.82842712474619 * fConst39);
		fConst43 = (fConst38 * fConst11);
		fConst44 = faustpower<2>(fConst39);
		fConst45 = (4 * fConst44);
		fConst46 = (fConst45 + (8 * fConst38));
		fConst47 = ((16 + (fConst16 * (fConst46 + (fConst43 * (fConst43 - fConst42))))) - fConst41);
		fConst48 = (5.65685424949238 * fConst39);
		fConst49 = (4 * fConst43);
		fConst50 = (fConst38 * fConst20);
		fConst51 = (22.62741699796952 * fConst40);
		fConst52 = ((fConst51 + (fConst50 * (fConst49 - fConst48))) - 64);
		fConst53 = ((fConst50 * (fConst48 + fConst49)) - (64 + fConst51));
		fConst54 = (8 * fConst44);
		fConst55 = (96 + (fConst16 * ((0 - (fConst54 + (16 * fConst38))) + (6 * (faustpower<4>(fConst37) * fConst16)))));
		fConst56 = (16 + (fConst41 + (fConst16 * (fConst46 + (fConst43 * (fConst43 + fConst42))))));
		fConst57 = (1.0 / fConst56);
		for (int i=0; i<5; i++) fRec7[i] = 0;
		fConst58 = (0 - fConst54);
		fConst59 = (fConst16 / fConst56);
		fConst60 = tan((2513.2741228718346 / double(iConst0)));
		fConst61 = (iConst0 * fConst60);
		fConst62 = sqrt((4.0 * ((iConst4 * fConst60) * fConst35)));
		fConst63 = faustpower<2>(fConst62);
		fConst64 = ((2.0 * fConst61) - (0.5 * (fConst63 / fConst61)));
		fConst65 = (fConst64 / fConst1);
		fConst66 = (11.31370849898476 * fConst65);
		fConst67 = (2.82842712474619 * fConst64);
		fConst68 = (fConst63 * fConst11);
		fConst69 = faustpower<2>(fConst64);
		fConst70 = (4 * fConst69);
		fConst71 = (fConst70 + (8 * fConst63));
		fConst72 = ((16 + (fConst16 * (fConst71 + (fConst68 * (fConst68 - fConst67))))) - fConst66);
		fConst73 = (5.65685424949238 * fConst64);
		fConst74 = (4 * fConst68);
		fConst75 = (fConst63 * fConst20);
		fConst76 = (22.62741699796952 * fConst65);
		fConst77 = ((fConst76 + (fConst75 * (fConst74 - fConst73))) - 64);
		fConst78 = ((fConst75 * (fConst73 + fConst74)) - (64 + fConst76));
		fConst79 = (8 * fConst69);
		fConst80 = (96 + (fConst16 * ((0 - (fConst79 + (16 * fConst63))) + (6 * (faustpower<4>(fConst62) * fConst16)))));
		fConst81 = (16 + (fConst66 + (fConst16 * (fConst71 + (fConst68 * (fConst68 + fConst67))))));
		fConst82 = (1.0 / fConst81);
		for (int i=0; i<5; i++) fRec8[i] = 0;
		fConst83 = (0 - fConst79);
		fConst84 = (fConst16 / fConst81);
		fConst85 = tan((5026.548245743669 / double(iConst0)));
		fConst86 = (iConst0 * fConst85);
		fConst87 = sqrt((4.0 * ((iConst4 * fConst85) * fConst60)));
		fConst88 = faustpower<2>(fConst87);
		fConst89 = ((2.0 * fConst86) - (0.5 * (fConst88 / fConst86)));
		fConst90 = (fConst89 / fConst1);
		fConst91 = (11.31370849898476 * fConst90);
		fConst92 = (2.82842712474619 * fConst89);
		fConst93 = (fConst88 * fConst11);
		fConst94 = faustpower<2>(fConst89);
		fConst95 = (4 * fConst94);
		fConst96 = (fConst95 + (8 * fConst88));
		fConst97 = ((16 + (fConst16 * (fConst96 + (fConst93 * (fConst93 - fConst92))))) - fConst91);
		fConst98 = (5.65685424949238 * fConst89);
		fConst99 = (4 * fConst93);
		fConst100 = (fConst88 * fConst20);
		fConst101 = (22.62741699796952 * fConst90);
		fConst102 = ((fConst101 + (fConst100 * (fConst99 - fConst98))) - 64);
		fConst103 = ((fConst100 * (fConst98 + fConst99)) - (64 + fConst101));
		fConst104 = (8 * fConst94);
		fConst105 = (96 + (fConst16 * ((0 - (fConst104 + (16 * fConst88))) + (6 * (faustpower<4>(fConst87) * fConst16)))));
		fConst106 = (16 + (fConst91 + (fConst16 * (fConst96 + (fConst93 * (fConst93 + fConst92))))));
		fConst107 = (1.0 / fConst106);
		for (int i=0; i<5; i++) fRec9[i] = 0;
		fConst108 = (0 - fConst104);
		fConst109 = (fConst16 / fConst106);
		fConst110 = tan((10053.096491487338 / double(iConst0)));
		fConst111 = (iConst0 * fConst110);
		fConst112 = sqrt((4.0 * ((iConst4 * fConst110) * fConst85)));
		fConst113 = faustpower<2>(fConst112);
		fConst114 = ((2.0 * fConst111) - (0.5 * (fConst113 / fConst111)));
		fConst115 = (fConst114 / fConst1);
		fConst116 = (11.31370849898476 * fConst115);
		fConst117 = (2.82842712474619 * fConst114);
		fConst118 = (fConst113 * fConst11);
		fConst119 = faustpower<2>(fConst114);
		fConst120 = (4 * fConst119);
		fConst121 = (fConst120 + (8 * fConst113));
		fConst122 = ((16 + (fConst16 * (fConst121 + (fConst118 * (fConst118 - fConst117))))) - fConst116);
		fConst123 = (5.65685424949238 * fConst114);
		fConst124 = (4 * fConst118);
		fConst125 = (fConst113 * fConst20);
		fConst126 = (22.62741699796952 * fConst115);
		fConst127 = ((fConst126 + (fConst125 * (fConst124 - fConst123))) - 64);
		fConst128 = ((fConst125 * (fConst123 + fConst124)) - (64 + fConst126));
		fConst129 = (8 * fConst119);
		fConst130 = (96 + (fConst16 * ((0 - (fConst129 + (16 * fConst113))) + (6 * (faustpower<4>(fConst112) * fConst16)))));
		fConst131 = (16 + (fConst116 + (fConst16 * (fConst121 + (fConst118 * (fConst118 + fConst117))))));
		fConst132 = (1.0 / fConst131);
		for (int i=0; i<5; i++) fRec10[i] = 0;
		fConst133 = (0 - fConst129);
		fConst134 = (fConst16 / fConst131);
		fConst135 = tan((20106.192982974677 / double(iConst0)));
		fConst136 = (iConst0 * fConst135);
		fConst137 = sqrt((4.0 * ((iConst4 * fConst135) * fConst110)));
		fConst138 = faustpower<2>(fConst137);
		fConst139 = ((2.0 * fConst136) - (0.5 * (fConst138 / fConst136)));
		fConst140 = (fConst139 / fConst1);
		fConst141 = (11.31370849898476 * fConst140);
		fConst142 = (2.82842712474619 * fConst139);
		fConst143 = (fConst138 * fConst11);
		fConst144 = faustpower<2>(fConst139);
		fConst145 = (4 * fConst144);
		fConst146 = (fConst145 + (8 * fConst138));
		fConst147 = ((16 + (fConst16 * (fConst146 + (fConst143 * (fConst143 - fConst142))))) - fConst141);
		fConst148 = (5.65685424949238 * fConst139);
		fConst149 = (4 * fConst143);
		fConst150 = (fConst138 * fConst20);
		fConst151 = (22.62741699796952 * fConst140);
		fConst152 = ((fConst151 + (fConst150 * (fConst149 - fConst148))) - 64);
		fConst153 = ((fConst150 * (fConst148 + fConst149)) - (64 + fConst151));
		fConst154 = (8 * fConst144);
		fConst155 = (96 + (fConst16 * ((0 - (fConst154 + (16 * fConst138))) + (6 * (faustpower<4>(fConst137) * fConst16)))));
		fConst156 = (16 + (fConst141 + (fConst16 * (fConst146 + (fConst143 * (fConst143 + fConst142))))));
		fConst157 = (1.0 / fConst156);
		for (int i=0; i<5; i++) fRec11[i] = 0;
		fConst158 = (0 - fConst154);
		fConst159 = (fConst16 / fConst156);
		fConst160 = tan((40212.385965949354 / double(iConst0)));
		fConst161 = (iConst0 * fConst160);
		fConst162 = sqrt((4.0 * ((iConst4 * fConst160) * fConst135)));
		fConst163 = faustpower<2>(fConst162);
		fConst164 = ((2.0 * fConst161) - (0.5 * (fConst163 / fConst161)));
		fConst165 = (fConst164 / fConst1);
		fConst166 = (11.31370849898476 * fConst165);
		fConst167 = (2.82842712474619 * fConst164);
		fConst168 = (fConst163 * fConst11);
		fConst169 = faustpower<2>(fConst164);
		fConst170 = (4 * fConst169);
		fConst171 = (fConst170 + (8 * fConst163));
		fConst172 = ((16 + (fConst16 * (fConst171 + (fConst168 * (fConst168 - fConst167))))) - fConst166);
		fConst173 = (5.65685424949238 * fConst164);
		fConst174 = (4 * fConst168);
		fConst175 = (fConst163 * fConst20);
		fConst176 = (22.62741699796952 * fConst165);
		fConst177 = ((fConst176 + (fConst175 * (fConst174 - fConst173))) - 64);
		fConst178 = ((fConst175 * (fConst173 + fConst174)) - (64 + fConst176));
		fConst179 = (8 * fConst169);
		fConst180 = (96 + (fConst16 * ((0 - (fConst179 + (16 * fConst163))) + (6 * (faustpower<4>(fConst162) * fConst16)))));
		fConst181 = (16 + (fConst166 + (fConst16 * (fConst171 + (fConst168 * (fConst168 + fConst167))))));
		fConst182 = (1.0 / fConst181);
		for (int i=0; i<5; i++) fRec12[i] = 0;
		fConst183 = (0 - fConst179);
		fConst184 = (fConst16 / fConst181);
		fConst185 = tan((138544.23602330987 / double(iConst0)));
		fConst186 = (iConst0 * fConst185);
		fConst187 = sqrt((4.0 * ((iConst4 * fConst185) * fConst160)));
		fConst188 = faustpower<2>(fConst187);
		fConst189 = ((2.0 * fConst186) - (0.5 * (fConst188 / fConst186)));
		fConst190 = (fConst189 / fConst1);
		fConst191 = (11.31370849898476 * fConst190);
		fConst192 = (2.82842712474619 * fConst189);
		fConst193 = (fConst188 * fConst11);
		fConst194 = faustpower<2>(fConst189);
		fConst195 = (4 * fConst194);
		fConst196 = (fConst195 + (8 * fConst188));
		fConst197 = ((16 + (fConst16 * (fConst196 + (fConst193 * (fConst193 - fConst192))))) - fConst191);
		fConst198 = (5.65685424949238 * fConst189);
		fConst199 = (4 * fConst193);
		fConst200 = (fConst188 * fConst20);
		fConst201 = (22.62741699796952 * fConst190);
		fConst202 = ((fConst201 + (fConst200 * (fConst199 - fConst198))) - 64);
		fConst203 = ((fConst200 * (fConst198 + fConst199)) - (64 + fConst201));
		fConst204 = (8 * fConst194);
		fConst205 = (96 + (fConst16 * ((0 - (fConst204 + (16 * fConst188))) + (6 * (faustpower<4>(fConst187) * fConst16)))));
		fConst206 = (16 + (fConst191 + (fConst16 * (fConst196 + (fConst193 * (fConst193 + fConst192))))));
		fConst207 = (1.0 / fConst206);
		for (int i=0; i<5; i++) fRec13[i] = 0;
		fConst208 = (0 - fConst204);
		fConst209 = (fConst16 / fConst206);
		for (int i=0; i<5; i++) fRec14[i] = 0;
		for (int i=0; i<5; i++) fRec15[i] = 0;
		for (int i=0; i<5; i++) fRec16[i] = 0;
		for (int i=0; i<5; i++) fRec17[i] = 0;
		for (int i=0; i<5; i++) fRec18[i] = 0;
		for (int i=0; i<5; i++) fRec19[i] = 0;
		for (int i=0; i<5; i++) fRec20[i] = 0;
		for (int i=0; i<5; i++) fRec21[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("0x00");
		interface->addHorizontalSlider("gainD", &fslider2, 1.0, 0.1, 1.9, 0.01);
		interface->addHorizontalSlider("gainS", &fslider5, 1.0, 0.1, 1.9, 0.01);
		interface->addHorizontalSlider("ratio1", &fslider4, 5.0, 1.0, 2e+01, 0.01);
		interface->addHorizontalSlider("ratio2", &fslider1, 5.0, 1.0, 2e+01, 0.01);
		interface->addHorizontalSlider("thresh1", &fslider3, -3e+01, -1e+02, 0.0, 1.0);
		interface->addHorizontalSlider("thresh2", &fslider0, -3e+01, -1e+02, 0.0, 1.0);
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		double 	fSlow0 = double(fslider0);
		double 	fSlow1 = (fConst32 * ((1.0 / double(double(fslider1))) - 1.0));
		double 	fSlow2 = double(fslider2);
		double 	fSlow3 = double(fslider3);
		double 	fSlow4 = (fConst32 * ((1.0 / double(double(fslider4))) - 1.0));
		double 	fSlow5 = double(fslider5);
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		FAUSTFLOAT* output2 = output[2];
		FAUSTFLOAT* output3 = output[3];
		FAUSTFLOAT* output4 = output[4];
		FAUSTFLOAT* output5 = output[5];
		FAUSTFLOAT* output6 = output[6];
		FAUSTFLOAT* output7 = output[7];
		FAUSTFLOAT* output8 = output[8];
		FAUSTFLOAT* output9 = output[9];
		FAUSTFLOAT* output10 = output[10];
		FAUSTFLOAT* output11 = output[11];
		FAUSTFLOAT* output12 = output[12];
		FAUSTFLOAT* output13 = output[13];
		FAUSTFLOAT* output14 = output[14];
		FAUSTFLOAT* output15 = output[15];
		for (int i=0; i<count; i++) {
			double fTemp0 = (double)input1[i];
			double fTemp1 = (double)input0[i];
			double fTemp2 = (fTemp1 - fTemp0);
			double fTemp3 = fabs(fTemp2);
			double fTemp4 = ((int((fRec2[1] > fTemp3)))?fConst30:fConst29);
			fRec3[0] = ((fRec3[1] * fTemp4) + (fTemp3 * (1.0 - fTemp4)));
			fRec2[0] = fRec3[0];
			fRec1[0] = ((fConst31 * fRec1[1]) + (fSlow1 * max(((20 * log10(fRec2[0])) - fSlow0), 0.0)));
			double fTemp5 = (fSlow2 * (fTemp2 * pow(10,(0.05 * fRec1[0]))));
			double fTemp6 = (fTemp1 + fTemp0);
			double fTemp7 = fabs(fTemp6);
			double fTemp8 = ((int((fRec5[1] > fTemp7)))?fConst30:fConst29);
			fRec6[0] = ((fRec6[1] * fTemp8) + (fTemp7 * (1.0 - fTemp8)));
			fRec5[0] = fRec6[0];
			fRec4[0] = ((fConst31 * fRec4[1]) + (fSlow4 * max(((20 * log10(fRec5[0])) - fSlow3), 0.0)));
			double fTemp9 = (fSlow5 * (fTemp6 * pow(10,(0.05 * fRec4[0]))));
			double fTemp10 = (0.6 * (fTemp9 + fTemp5));
			fRec0[0] = (fTemp10 - (fConst28 * ((((fConst26 * fRec0[2]) + (fConst24 * fRec0[1])) + (fConst23 * fRec0[3])) + (fConst17 * fRec0[4]))));
			output0[i] = (FAUSTFLOAT)(fConst34 * (((fConst33 * fRec0[2]) + (fConst14 * fRec0[0])) + (fConst14 * fRec0[4])));
			fRec7[0] = (fTemp10 - (fConst57 * ((((fConst55 * fRec7[2]) + (fConst53 * fRec7[1])) + (fConst52 * fRec7[3])) + (fConst47 * fRec7[4]))));
			output1[i] = (FAUSTFLOAT)(fConst59 * (((fConst45 * fRec7[0]) + (fConst58 * fRec7[2])) + (fConst45 * fRec7[4])));
			fRec8[0] = (fTemp10 - (fConst82 * ((((fConst80 * fRec8[2]) + (fConst78 * fRec8[1])) + (fConst77 * fRec8[3])) + (fConst72 * fRec8[4]))));
			output2[i] = (FAUSTFLOAT)(fConst84 * (((fConst70 * fRec8[0]) + (fConst83 * fRec8[2])) + (fConst70 * fRec8[4])));
			fRec9[0] = (fTemp10 - (fConst107 * ((((fConst105 * fRec9[2]) + (fConst103 * fRec9[1])) + (fConst102 * fRec9[3])) + (fConst97 * fRec9[4]))));
			output3[i] = (FAUSTFLOAT)(fConst109 * (((fConst95 * fRec9[0]) + (fConst108 * fRec9[2])) + (fConst95 * fRec9[4])));
			fRec10[0] = (fTemp10 - (fConst132 * ((((fConst130 * fRec10[2]) + (fConst128 * fRec10[1])) + (fConst127 * fRec10[3])) + (fConst122 * fRec10[4]))));
			output4[i] = (FAUSTFLOAT)(fConst134 * (((fConst120 * fRec10[0]) + (fConst133 * fRec10[2])) + (fConst120 * fRec10[4])));
			fRec11[0] = (fTemp10 - (fConst157 * ((((fConst155 * fRec11[2]) + (fConst153 * fRec11[1])) + (fConst152 * fRec11[3])) + (fConst147 * fRec11[4]))));
			output5[i] = (FAUSTFLOAT)(fConst159 * (((fConst145 * fRec11[0]) + (fConst158 * fRec11[2])) + (fConst145 * fRec11[4])));
			fRec12[0] = (fTemp10 - (fConst182 * ((((fConst180 * fRec12[2]) + (fConst178 * fRec12[1])) + (fConst177 * fRec12[3])) + (fConst172 * fRec12[4]))));
			output6[i] = (FAUSTFLOAT)(fConst184 * (((fConst170 * fRec12[0]) + (fConst183 * fRec12[2])) + (fConst170 * fRec12[4])));
			fRec13[0] = (fTemp10 - (fConst207 * ((((fConst205 * fRec13[2]) + (fConst203 * fRec13[1])) + (fConst202 * fRec13[3])) + (fConst197 * fRec13[4]))));
			output7[i] = (FAUSTFLOAT)(fConst209 * (((fConst195 * fRec13[0]) + (fConst208 * fRec13[2])) + (fConst195 * fRec13[4])));
			double fTemp11 = (0.6 * (fTemp9 - fTemp5));
			fRec14[0] = (fTemp11 - (fConst28 * ((((fConst26 * fRec14[2]) + (fConst24 * fRec14[1])) + (fConst23 * fRec14[3])) + (fConst17 * fRec14[4]))));
			output8[i] = (FAUSTFLOAT)(fConst34 * (((fConst14 * fRec14[0]) + (fConst33 * fRec14[2])) + (fConst14 * fRec14[4])));
			fRec15[0] = (fTemp11 - (fConst57 * ((((fConst55 * fRec15[2]) + (fConst53 * fRec15[1])) + (fConst52 * fRec15[3])) + (fConst47 * fRec15[4]))));
			output9[i] = (FAUSTFLOAT)(fConst59 * (((fConst45 * fRec15[0]) + (fConst58 * fRec15[2])) + (fConst45 * fRec15[4])));
			fRec16[0] = (fTemp11 - (fConst82 * ((((fConst80 * fRec16[2]) + (fConst78 * fRec16[1])) + (fConst77 * fRec16[3])) + (fConst72 * fRec16[4]))));
			output10[i] = (FAUSTFLOAT)(fConst84 * (((fConst70 * fRec16[0]) + (fConst83 * fRec16[2])) + (fConst70 * fRec16[4])));
			fRec17[0] = (fTemp11 - (fConst107 * ((((fConst105 * fRec17[2]) + (fConst103 * fRec17[1])) + (fConst102 * fRec17[3])) + (fConst97 * fRec17[4]))));
			output11[i] = (FAUSTFLOAT)(fConst109 * (((fConst95 * fRec17[0]) + (fConst108 * fRec17[2])) + (fConst95 * fRec17[4])));
			fRec18[0] = (fTemp11 - (fConst132 * ((((fConst130 * fRec18[2]) + (fConst128 * fRec18[1])) + (fConst127 * fRec18[3])) + (fConst122 * fRec18[4]))));
			output12[i] = (FAUSTFLOAT)(fConst134 * (((fConst120 * fRec18[0]) + (fConst133 * fRec18[2])) + (fConst120 * fRec18[4])));
			fRec19[0] = (fTemp11 - (fConst157 * ((((fConst155 * fRec19[2]) + (fConst153 * fRec19[1])) + (fConst152 * fRec19[3])) + (fConst147 * fRec19[4]))));
			output13[i] = (FAUSTFLOAT)(fConst159 * (((fConst145 * fRec19[0]) + (fConst158 * fRec19[2])) + (fConst145 * fRec19[4])));
			fRec20[0] = (fTemp11 - (fConst182 * ((((fConst180 * fRec20[2]) + (fConst178 * fRec20[1])) + (fConst177 * fRec20[3])) + (fConst172 * fRec20[4]))));
			output14[i] = (FAUSTFLOAT)(fConst184 * (((fConst170 * fRec20[0]) + (fConst183 * fRec20[2])) + (fConst170 * fRec20[4])));
			fRec21[0] = (fTemp11 - (fConst207 * ((((fConst205 * fRec21[2]) + (fConst203 * fRec21[1])) + (fConst202 * fRec21[3])) + (fConst197 * fRec21[4]))));
			output15[i] = (FAUSTFLOAT)(fConst209 * (((fConst195 * fRec21[0]) + (fConst208 * fRec21[2])) + (fConst195 * fRec21[4])));
			// post processing
			for (int i=4; i>0; i--) fRec21[i] = fRec21[i-1];
			for (int i=4; i>0; i--) fRec20[i] = fRec20[i-1];
			for (int i=4; i>0; i--) fRec19[i] = fRec19[i-1];
			for (int i=4; i>0; i--) fRec18[i] = fRec18[i-1];
			for (int i=4; i>0; i--) fRec17[i] = fRec17[i-1];
			for (int i=4; i>0; i--) fRec16[i] = fRec16[i-1];
			for (int i=4; i>0; i--) fRec15[i] = fRec15[i-1];
			for (int i=4; i>0; i--) fRec14[i] = fRec14[i-1];
			for (int i=4; i>0; i--) fRec13[i] = fRec13[i-1];
			for (int i=4; i>0; i--) fRec12[i] = fRec12[i-1];
			for (int i=4; i>0; i--) fRec11[i] = fRec11[i-1];
			for (int i=4; i>0; i--) fRec10[i] = fRec10[i-1];
			for (int i=4; i>0; i--) fRec9[i] = fRec9[i-1];
			for (int i=4; i>0; i--) fRec8[i] = fRec8[i-1];
			for (int i=4; i>0; i--) fRec7[i] = fRec7[i-1];
			for (int i=4; i>0; i--) fRec0[i] = fRec0[i-1];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
		}
	}
};



/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/


/* Faust code wrapper ------- */

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "jpatcher_api.h"
#include <string.h>

#define ASSIST_INLET 	1  		/* should be defined somewhere ?? */
#define ASSIST_OUTLET 	2		/* should be defined somewhere ?? */

#define EXTERNAL_VERSION "0.55"

static const char* getCodeSize()
{
    int tmp;
    return (sizeof(&tmp) == 8) ? "64 bits" : "32 bits";
}

class mspUI;

struct Max_Meta1 : Meta
{
    int fCount;
    
    Max_Meta1():fCount(0)
    {}
     
    void declare(const char* key, const char* value)
    {
        if ((strcmp("name", key) == 0) || (strcmp("author", key) == 0)) {
            fCount++;
        }
    }
};

struct Max_Meta2 : Meta
{
    void declare(const char* key, const char* value)
    {
        if ((strcmp("name", key) == 0) || (strcmp("author", key) == 0)) {
            post("%s : %s", key, value);
        }
    }
};


/*--------------------------------------------------------------------------*/
typedef struct faust
{
    t_pxobject m_ob;
    t_atom *m_seen, *m_want;
    map<string, t_object*> m_output_table;
    short m_where;
    bool m_mute;
    void** args;
    mspUI* dspUI;
    mydsp* dsp;
    char* m_json;
} t_faust;

void *faust_class;

/*--------------------------------------------------------------------------*/
class mspUIObject {

	protected:

		string fLabel;
		FAUSTFLOAT* fZone;

		FAUSTFLOAT range(FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT val) {return (val < min) ? min : (val > max) ? max : val;}

	public:

		mspUIObject(const string& label, FAUSTFLOAT* zone):fLabel(label),fZone(zone) {}
		virtual ~mspUIObject() {}

		virtual void setValue(FAUSTFLOAT f) {*fZone = range(0.0,1.0,f);}
        virtual FAUSTFLOAT getValue() { return *fZone; }
		virtual void toString(char* buffer) {}
		virtual string getName() {return fLabel;}
};

/*--------------------------------------------------------------------------*/
class mspCheckButton : public mspUIObject {

	public:

		mspCheckButton(const string& label, FAUSTFLOAT* zone):mspUIObject(label,zone) {}
		virtual ~mspCheckButton() {}

		void toString(char* buffer)
		{
            sprintf(buffer, "CheckButton(double): %s", fLabel.c_str());
		}
};

/*--------------------------------------------------------------------------*/
class mspButton : public mspUIObject {

	public:

		mspButton(const string& label, FAUSTFLOAT* zone):mspUIObject(label,zone) {}
		virtual ~mspButton() {}

		void toString(char* buffer)
		{
            sprintf(buffer, "Button(double): %s", fLabel.c_str());
		}
};

/*--------------------------------------------------------------------------*/
class mspSlider : public mspUIObject {

	private:

		FAUSTFLOAT fInit;
		FAUSTFLOAT fMin;
		FAUSTFLOAT fMax;
		FAUSTFLOAT fStep;

	public:

		mspSlider(const string& label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
			:mspUIObject(label,zone),fInit(init),fMin(min),fMax(max),fStep(step) {}
		virtual ~mspSlider() {}

		void toString(char* buffer)
		{
            stringstream s; 
            s << "Slider(double): " << fLabel << " [init=" << fInit << ":min=" << fMin << ":max=" << fMax << ":step=" << fStep << ":cur=" << *fZone << "]";
            strcpy(buffer, s.str().c_str());
		}

		void setValue(FAUSTFLOAT f) {*fZone = range(fMin,fMax,f);}
};

/*--------------------------------------------------------------------------*/
class mspBargraph : public mspUIObject {
    
    private:
        
        FAUSTFLOAT fMin;
        FAUSTFLOAT fMax;
        FAUSTFLOAT fCurrent;
        
    public:
        
        mspBargraph(const string& label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        :mspUIObject(label,zone),fMin(min),fMax(max),fCurrent(*zone) {}
        virtual ~mspBargraph() {}
        
        void toString(char* buffer)
        {
            stringstream s; 
            s << "Bargraph(float): " << fLabel << " [min=" << fMin << ":max=" << fMax << ":cur=" << *fZone << "]";
            strcpy(buffer, s.str().c_str());
        }
        
        virtual FAUSTFLOAT getValue() 
        { 
            if (*fZone != fCurrent) {
                fCurrent = *fZone;
                return fCurrent;
            } else {
                return NAN; 
            }
        }
};

/*--------------------------------------------------------------------------*/

#define MULTI_SIZE  256

class mspUI : public UI
{
	private:

        map<string, mspUIObject*> fUITable1;       // Table using labels
        map<string, mspUIObject*> fUITable2;       // Table using complete path
        map<string, mspUIObject*> fUITable3;       // Table containing bargraph
       
        map<const char*, const char*> fDeclareTable;
        std::vector<std::string> fControlsLevel;
        
        FAUSTFLOAT* fMultiTable[MULTI_SIZE];
        int fMultiIndex;
        int fMultiControl;
        
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
        string createLabel(const char* label)
        {
            map<const char*, const char*>::reverse_iterator it;
            if (fDeclareTable.size() > 0) {
                unsigned int i = 0;
                string res = string(label);
                char sep = '[';
                for (it = fDeclareTable.rbegin(); it != fDeclareTable.rend(); it++, i++) {
                    res = res + sep + (*it).first + ":" + (*it).second;
                    sep = ',';
                }
                res += ']';
                fDeclareTable.clear();
                return res;
            } else {
                return string(label);
            }
        }

	public:
    
		typedef map<string, mspUIObject*>::iterator iterator;

		mspUI() 
        {
     		for (int i = 0; i < MULTI_SIZE; i++) {
                fMultiTable[i] = 0;
            }
            fMultiIndex = fMultiControl = 0;
        }
		virtual ~mspUI()
		{
            clear();
   		}
      
		void addButton(const char* label, FAUSTFLOAT* zone) 
        {
            mspUIObject* obj = new mspButton(createLabel(label), zone);
            fUITable1[string(label)] = obj;
            fUITable2[buildPath(label)] = obj;
        }
        
        void addCheckButton(const char* label, FAUSTFLOAT* zone) 
        {
            mspUIObject* obj = new mspCheckButton(createLabel(label), zone);
            fUITable1[string(label)] = obj;
            fUITable2[buildPath(label)] = obj; 
        }
        
        void addSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            mspUIObject* obj = new mspSlider(createLabel(label), zone, init, min, max, step);
            fUITable1[string(label)] = obj;
            fUITable2[buildPath(label)] = obj; 
        }
        
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addSlider(label, zone, init, min, max, step);
        }
        
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addSlider(label, zone, init, min, max, step);
        }
        
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            mspUIObject* obj = new mspSlider(createLabel(label), zone, init, min, max, step);
            fUITable1[string(label)] = obj;
            fUITable2[buildPath(label)] = obj;
        }
        
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {   
            fUITable3[buildPath(label)] = new mspBargraph(createLabel(label), zone, min, max);
            fDeclareTable.clear();
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            fUITable3[buildPath(label)] = new mspBargraph(createLabel(label), zone, min, max);
            fDeclareTable.clear();
        }
    
        void openTabBox(const char* label) {fControlsLevel.push_back(label); fDeclareTable.clear();}
        void openHorizontalBox(const char* label) {fControlsLevel.push_back(label); fDeclareTable.clear();}
        void openVerticalBox(const char* label) {fControlsLevel.push_back(label); fDeclareTable.clear();}
        void closeBox() {fControlsLevel.pop_back(); fDeclareTable.clear();}

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            if (strcmp(key,"multi") == 0) {
                int index = atoi(val);
                if (index >= 0 && index < MULTI_SIZE) {
                    fMultiTable[index] = zone;
                    fMultiControl++;
                } else {
                    post("Invalid multi index = %d", index);
                }
            }
            
            fDeclareTable[key] = val;
        }
        
        void setMultiValues(FAUSTFLOAT* multi, int buffer_size)
		{
            for (int read = 0; read < buffer_size; read++) {
                int write = (fMultiIndex + read) & (MULTI_SIZE - 1);
                if (fMultiTable[write]) {
                    *fMultiTable[write] = multi[read];
                }
            }
            fMultiIndex += buffer_size;
		}
        
        bool isMulti() { return fMultiControl > 0; }
    
        bool isValue(string name) 
        {
            return (fUITable1.count(name) || fUITable2.count(name));
        }
        bool isOutputValue(string name) 
        {
            return fUITable3.count(name);
        }
        bool isInputValue(string name) 
        {
            return fUITable2.count(name);
        }
        bool setValue(string name, FAUSTFLOAT f)
        {
            if (fUITable1.count(name)) {
                fUITable1[name]->setValue(f);
                return true;
            } else if (fUITable2.count(name)) {
                fUITable2[name]->setValue(f);
                return true;
            } else {
                return false;
            }
        }
		FAUSTFLOAT getOutputValue(string name) { return fUITable3[name]->getValue(); }
          
        iterator begin1()	{ return fUITable1.begin(); }
        iterator end1()		{ return fUITable1.end(); }
        
        iterator begin2()	{ return fUITable2.begin(); }
        iterator end2()		{ return fUITable2.end(); }

        int itemsCount() { return fUITable1.size(); }
        void clear() 
        { 
            iterator it;
            for (it = begin1(); it != end1(); it++) {
                delete (*it).second;
            }
            fUITable1.clear(); 
            fUITable2.clear(); 
        }
};

//--------------------------------------------------------------------------
static bool check_digit(const string& name)
{
    for (int i = name.size() - 1; i >= 0; i--) {
        if (isdigit(name[i])) return true;
    }
    return false;
}

static int count_digit(const string& name)
{
    int count = 0;
    for (int i = name.size() - 1; i >= 0; i--) {
        if (isdigit(name[i])) count++;
    }
    return count;
}

void faust_anything(t_faust* obj, t_symbol* s, short ac, t_atom* av)
{
    bool res = false;
    string name = string((s)->s_name);
     
    if (ac < 0) return;
    
    // Check if no argument is there, consider it is a toggle message for a button
    if (ac == 0 && obj->dspUI->isValue(name)) {
        
        string name = string((s)->s_name);
        float off = 0.0f;
        float on = 1.0f;
        obj->dspUI->setValue(name, off);
        obj->dspUI->setValue(name, on);
        
        av[0].a_type = A_FLOAT;
        av[0].a_w.w_float = off;
        faust_anything(obj, s, 1, av);
        
        return;
    }
    
    // List of values
    if (check_digit(name)) {
        
        int ndigit = 0;
        int pos;
        
        for (pos = name.size() - 1; pos >= 0; pos--) {
            if (isdigit(name[pos]) || name[pos] == ' ') {
                ndigit++;
            } else {
                break;
            }
        }
        pos++;
        
        string prefix = name.substr(0, pos);
        string num_base = name.substr(pos);
        int num = atoi(num_base.c_str());
        
        int i;
        t_atom* ap;
       
        // Increment ap each time to get to the next atom
        for (i = 0, ap = av; i < ac; i++, ap++) {
            float value;
            switch (atom_gettype(ap)) {
                case A_LONG: {
                    value = (float)ap[0].a_w.w_long;
                    break;
                }
                case A_FLOAT:
                    value = ap[0].a_w.w_float;
                    break;
                    
                default:
                    post("Invalid argument in parameter setting"); 
                    return;         
            }
            
            stringstream num_val;
            num_val << num + i;
            char param_name[256];
            
            switch (ndigit - count_digit(num_val.str())) {
                case 0: 
                    sprintf(param_name, "%s%s", prefix.c_str(), num_val.str().c_str());
                    break;
                case 1: 
                    sprintf(param_name, "%s %s", prefix.c_str(), num_val.str().c_str());
                    break;
                case 2: 
                    sprintf(param_name, "%s  %s", prefix.c_str(), num_val.str().c_str());
                    break;
            }
            
            // Try special naming scheme for list of parameters
            res = obj->dspUI->setValue(param_name, value); 
            
            // Otherwise try standard name
            if (!res) {
                res = obj->dspUI->setValue(name, value);
            }
            
            if (!res) {
                post("Unknown parameter : %s", (s)->s_name);
            }
        }
    } else {
        // Standard parameter name
        float value = (av[0].a_type == A_LONG) ? (float)av[0].a_w.w_long : av[0].a_w.w_float;
        res = obj->dspUI->setValue(name, value);
    }
    
    if (!res) {
        post("Unknown parameter : %s", (s)->s_name);
    }
}

/*--------------------------------------------------------------------------*/
void faust_create_jsui(t_faust* x)
{
    t_object *patcher, *box, *obj;
    object_obex_lookup((t_object*)x, gensym("#P"), &patcher);
    
    for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) {
        obj = jbox_get_object(box);
        // Notify JSON
        if (obj && strcmp(object_classname(obj)->s_name, "js") == 0) {
            t_atom json;
            atom_setsym(&json, gensym(x->m_json));
            object_method_typed(obj, gensym("anything"), 1, &json, 0);
            post("Generate UI from JSON...");
        }
    }
        
    // Keep all outputs
    x->m_output_table.clear();
    for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) {
        obj = jbox_get_object(box);
        t_symbol *scriptingname = jbox_get_varname(obj); // scripting name
        if (scriptingname && x->dspUI->isOutputValue(scriptingname->s_name)) {
            x->m_output_table[scriptingname->s_name] = obj;
        }
    }
}

void faust_update_outputs(t_faust* x)
{
    map<string, t_object*>::iterator it;
    for (it =  x->m_output_table.begin(); it != x->m_output_table.end(); it++) {
        FAUSTFLOAT value = x->dspUI->isOutputValue((*it).first);
        if (value != NAN) {
            t_atom at_value;
            atom_setfloat(&at_value, value);
            object_method_typed((*it).second, gensym("float"), 1, &at_value, 0);
        }
    }
}

/*--------------------------------------------------------------------------*/
void* faust_new(t_symbol* s, short ac, t_atom* av)
{
    t_faust* x = (t_faust*)newobject(faust_class);

    x->m_mute = false;

    x->dsp = new mydsp();
    x->dspUI = new mspUI();

    x->dsp->init(long(sys_getsr()));
    x->dsp->buildUserInterface(x->dspUI);
    
    // Prepare JSON
    JSONUI builder(x->dsp->getNumInputs(), x->dsp->getNumOutputs());
    x->dsp->metadata(&builder);
    x->dsp->buildUserInterface(&builder);
    x->m_json = strdup(builder.JSON().c_str());
    
    int num_input;
    
    if (x->dspUI->isMulti()) {
        num_input = x->dsp->getNumInputs() + 1;
    } else {
        num_input = x->dsp->getNumInputs();
    }
    
    x->args = (void**)calloc((num_input + x->dsp->getNumOutputs()) + 2, sizeof(void*));
    /* Multi in */
    dsp_setup((t_pxobject*)x, num_input);

    /* Multi out */
    for (int i = 0; i< x->dsp->getNumOutputs(); i++) {
        outlet_new((t_pxobject*)x, (char*)"signal");
    }

    ((t_pxobject*)x)->z_misc = Z_NO_INPLACE; // To assure input and output buffers are actually different
    
    // send JSON to JS script
    faust_create_jsui(x);
    return x;
}

/*--------------------------------------------------------------------------*/
void faust_dblclick(t_faust* x, long inlet)
{
    post((char*)"------------------");
    for (mspUI::iterator it = x->dspUI->begin1(); it != x->dspUI->end1(); ++it) {
        char param[256];
        it->second->toString(param);
        post(param);
    }
}

/*--------------------------------------------------------------------------*/
//11/13/2015 : faust_assist is actually called at each click in the patcher... to we now use 'faust_dblclick' to display the parameters...
void faust_assist(t_faust* x, void* b, long msg, long a, char* dst)
{
    if (msg == ASSIST_INLET) {
        if (a == 0) {
            if (x->dsp->getNumInputs() == 0) {
                sprintf(dst, "(signal) : Unused Input");
            } else {
                sprintf(dst, "(signal) : Audio Input %ld", (a+1));
			}
            /*
			post((char*)"------------------");
			for (mspUI::iterator it = x->dspUI->begin1(); it != x->dspUI->end1(); ++it) {
				char param[256];
				it->second->toString(param);
				post(param);
			}
            */
        } else if (a < x->dsp->getNumInputs()) {
            sprintf(dst, "(signal) : Audio Input %ld", (a+1));
        }
    } else if (msg == ASSIST_OUTLET) {
        sprintf(dst, "(signal) : Audio Output %ld", (a+1));
    }
}

/*--------------------------------------------------------------------------*/
void faust_mute(t_faust* obj, t_symbol* s, short ac, t_atom* at)
{
    if (atom_gettype(at) == A_LONG) {
        obj->m_mute = atom_getlong(at);
    }
}

/*--------------------------------------------------------------------------*/
void faust_free(t_faust* x)
{
	dsp_free((t_pxobject*)x);
	if (x->dsp) delete x->dsp;
	if (x->dspUI) delete x->dspUI;
	if (x->args) free(x->args);
    if (x->m_json) free(x->m_json);
}

/*--------------------------------------------------------------------------*/
void faust_perform64(t_faust* x, t_object* dsp64, double** ins, long numins, double** outs, long numouts, long sampleframes, long flags, void* userparam)
{
    AVOIDDENORMALS;
    if (x->m_mute) {
        // Write null buffers to outs
        for (int i = 0; i < numouts; i++) {
             memset(outs[i], 0, sizeof(double) * sampleframes);
        }
    } else {
        if (x->dspUI->isMulti()) {
            x->dspUI->setMultiValues(ins[0], sampleframes);
            x->dsp->compute(sampleframes, ++ins, outs);
        } else {
            x->dsp->compute(sampleframes, ins, outs);
        }
        faust_update_outputs(x);
    }
}

/*--------------------------------------------------------------------------*/
void faust_dsp64(t_faust* x, t_object* dsp64, short* count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, faust_perform64, 0, NULL);
}

/*--------------------------------------------------------------------------*/
extern "C" int main(void)
{
	setup((t_messlist**)&faust_class, (method)faust_new, (method)faust_free,
		(short)sizeof(t_faust), 0L, A_DEFFLOAT, 0);

	dsp* thedsp = new mydsp();
    mspUI dspUI;
	thedsp->buildUserInterface(&dspUI);

    // 03/11/14 : use 'anything' to handle all parameter changes
    addmess((method)faust_anything, (char*)"anything", A_GIMME, 0);
    addmess((method)faust_dsp64, (char*)"dsp64", A_CANT, 0);
    addmess((method)faust_dblclick, (char*)"dblclick", A_CANT, 0);
    addmess((method)faust_assist, (char*)"assist", A_CANT, 0);
    addmess((method)faust_mute, (char*)"mute", A_GIMME, 0);
    dsp_initclass();

    post((char*)"Faust DSP object v%s (sample = 64 bits code = %s)", EXTERNAL_VERSION, getCodeSize());
    post((char*)"Copyright (c) 2012-2015 Grame");
    Max_Meta1 meta1;
    mydsp::metadata(&meta1);
    if (meta1.fCount > 0) {
        Max_Meta2 meta2;
        post("------------------------------");
        mydsp::metadata(&meta2);
        post("------------------------------");
    }
    
    delete(thedsp);
	return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/




