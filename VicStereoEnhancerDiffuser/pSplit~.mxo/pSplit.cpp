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
	int 	iVec0[2];
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
	double 	fRec3[2];
	double 	fRec4[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	double 	fConst30;
	FAUSTFLOAT 	fslider3;
	double 	fRec2[3];
	FAUSTFLOAT 	fslider4;
	double 	fRec6[3];
	FAUSTFLOAT 	fslider5;
	double 	fRec0[5];
	double 	fConst31;
	double 	fConst32;
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
	double 	fRec7[5];
	double 	fConst56;
	double 	fConst57;
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
	double 	fRec8[5];
	double 	fConst81;
	double 	fConst82;
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
	double 	fRec9[5];
	double 	fConst106;
	double 	fConst107;
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
	double 	fRec10[5];
	double 	fConst131;
	double 	fConst132;
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
	double 	fRec11[5];
	double 	fConst156;
	double 	fConst157;
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
	double 	fRec12[5];
	double 	fConst181;
	double 	fConst182;
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
	double 	fRec13[5];
	double 	fConst206;
	double 	fConst207;
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
		m->declare("oscillator.lib/name", "Faust Oscillator Library");
		m->declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("oscillator.lib/copyright", "Julius O. Smith III");
		m->declare("oscillator.lib/version", "1.11");
		m->declare("oscillator.lib/license", "STK-4.3");
	}

	virtual int getNumInputs() 	{ return 2; }
	virtual int getNumOutputs() 	{ return 16; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		for (int i=0; i<2; i++) iVec0[i] = 0;
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
		fslider0 = 2.0;
		fConst29 = (6.283185307179586 / double(iConst0));
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		fslider1 = 2.0;
		fslider2 = 2.0;
		fConst30 = (1.0 / double(iConst0));
		fslider3 = 5e+01;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		fslider4 = 1.0;
		for (int i=0; i<3; i++) fRec6[i] = 0;
		fslider5 = 1.0;
		for (int i=0; i<5; i++) fRec0[i] = 0;
		fConst31 = (0 - fConst25);
		fConst32 = (fConst16 / fConst27);
		fConst33 = tan((1256.6370614359173 / double(iConst0)));
		fConst34 = (iConst0 * fConst33);
		fConst35 = sqrt((4.0 * ((iConst4 * fConst33) * fConst2)));
		fConst36 = faustpower<2>(fConst35);
		fConst37 = ((2.0 * fConst34) - (0.5 * (fConst36 / fConst34)));
		fConst38 = (fConst37 / fConst1);
		fConst39 = (11.31370849898476 * fConst38);
		fConst40 = (2.82842712474619 * fConst37);
		fConst41 = (fConst36 * fConst11);
		fConst42 = faustpower<2>(fConst37);
		fConst43 = (4 * fConst42);
		fConst44 = (fConst43 + (8 * fConst36));
		fConst45 = ((16 + (fConst16 * (fConst44 + (fConst41 * (fConst41 - fConst40))))) - fConst39);
		fConst46 = (5.65685424949238 * fConst37);
		fConst47 = (4 * fConst41);
		fConst48 = (fConst36 * fConst20);
		fConst49 = (22.62741699796952 * fConst38);
		fConst50 = ((fConst49 + (fConst48 * (fConst47 - fConst46))) - 64);
		fConst51 = ((fConst48 * (fConst46 + fConst47)) - (64 + fConst49));
		fConst52 = (8 * fConst42);
		fConst53 = (96 + (fConst16 * ((0 - (fConst52 + (16 * fConst36))) + (6 * (faustpower<4>(fConst35) * fConst16)))));
		fConst54 = (16 + (fConst39 + (fConst16 * (fConst44 + (fConst41 * (fConst41 + fConst40))))));
		fConst55 = (1.0 / fConst54);
		for (int i=0; i<5; i++) fRec7[i] = 0;
		fConst56 = (0 - fConst52);
		fConst57 = (fConst16 / fConst54);
		fConst58 = tan((2513.2741228718346 / double(iConst0)));
		fConst59 = (iConst0 * fConst58);
		fConst60 = sqrt((4.0 * ((iConst4 * fConst58) * fConst33)));
		fConst61 = faustpower<2>(fConst60);
		fConst62 = ((2.0 * fConst59) - (0.5 * (fConst61 / fConst59)));
		fConst63 = (fConst62 / fConst1);
		fConst64 = (11.31370849898476 * fConst63);
		fConst65 = (2.82842712474619 * fConst62);
		fConst66 = (fConst61 * fConst11);
		fConst67 = faustpower<2>(fConst62);
		fConst68 = (4 * fConst67);
		fConst69 = (fConst68 + (8 * fConst61));
		fConst70 = ((16 + (fConst16 * (fConst69 + (fConst66 * (fConst66 - fConst65))))) - fConst64);
		fConst71 = (5.65685424949238 * fConst62);
		fConst72 = (4 * fConst66);
		fConst73 = (fConst61 * fConst20);
		fConst74 = (22.62741699796952 * fConst63);
		fConst75 = ((fConst74 + (fConst73 * (fConst72 - fConst71))) - 64);
		fConst76 = ((fConst73 * (fConst71 + fConst72)) - (64 + fConst74));
		fConst77 = (8 * fConst67);
		fConst78 = (96 + (fConst16 * ((0 - (fConst77 + (16 * fConst61))) + (6 * (faustpower<4>(fConst60) * fConst16)))));
		fConst79 = (16 + (fConst64 + (fConst16 * (fConst69 + (fConst66 * (fConst66 + fConst65))))));
		fConst80 = (1.0 / fConst79);
		for (int i=0; i<5; i++) fRec8[i] = 0;
		fConst81 = (0 - fConst77);
		fConst82 = (fConst16 / fConst79);
		fConst83 = tan((5026.548245743669 / double(iConst0)));
		fConst84 = (iConst0 * fConst83);
		fConst85 = sqrt((4.0 * ((iConst4 * fConst83) * fConst58)));
		fConst86 = faustpower<2>(fConst85);
		fConst87 = ((2.0 * fConst84) - (0.5 * (fConst86 / fConst84)));
		fConst88 = (fConst87 / fConst1);
		fConst89 = (11.31370849898476 * fConst88);
		fConst90 = (2.82842712474619 * fConst87);
		fConst91 = (fConst86 * fConst11);
		fConst92 = faustpower<2>(fConst87);
		fConst93 = (4 * fConst92);
		fConst94 = (fConst93 + (8 * fConst86));
		fConst95 = ((16 + (fConst16 * (fConst94 + (fConst91 * (fConst91 - fConst90))))) - fConst89);
		fConst96 = (5.65685424949238 * fConst87);
		fConst97 = (4 * fConst91);
		fConst98 = (fConst86 * fConst20);
		fConst99 = (22.62741699796952 * fConst88);
		fConst100 = ((fConst99 + (fConst98 * (fConst97 - fConst96))) - 64);
		fConst101 = ((fConst98 * (fConst96 + fConst97)) - (64 + fConst99));
		fConst102 = (8 * fConst92);
		fConst103 = (96 + (fConst16 * ((0 - (fConst102 + (16 * fConst86))) + (6 * (faustpower<4>(fConst85) * fConst16)))));
		fConst104 = (16 + (fConst89 + (fConst16 * (fConst94 + (fConst91 * (fConst91 + fConst90))))));
		fConst105 = (1.0 / fConst104);
		for (int i=0; i<5; i++) fRec9[i] = 0;
		fConst106 = (0 - fConst102);
		fConst107 = (fConst16 / fConst104);
		fConst108 = tan((10053.096491487338 / double(iConst0)));
		fConst109 = (iConst0 * fConst108);
		fConst110 = sqrt((4.0 * ((iConst4 * fConst108) * fConst83)));
		fConst111 = faustpower<2>(fConst110);
		fConst112 = ((2.0 * fConst109) - (0.5 * (fConst111 / fConst109)));
		fConst113 = (fConst112 / fConst1);
		fConst114 = (11.31370849898476 * fConst113);
		fConst115 = (2.82842712474619 * fConst112);
		fConst116 = (fConst111 * fConst11);
		fConst117 = faustpower<2>(fConst112);
		fConst118 = (4 * fConst117);
		fConst119 = (fConst118 + (8 * fConst111));
		fConst120 = ((16 + (fConst16 * (fConst119 + (fConst116 * (fConst116 - fConst115))))) - fConst114);
		fConst121 = (5.65685424949238 * fConst112);
		fConst122 = (4 * fConst116);
		fConst123 = (fConst111 * fConst20);
		fConst124 = (22.62741699796952 * fConst113);
		fConst125 = ((fConst124 + (fConst123 * (fConst122 - fConst121))) - 64);
		fConst126 = ((fConst123 * (fConst121 + fConst122)) - (64 + fConst124));
		fConst127 = (8 * fConst117);
		fConst128 = (96 + (fConst16 * ((0 - (fConst127 + (16 * fConst111))) + (6 * (faustpower<4>(fConst110) * fConst16)))));
		fConst129 = (16 + (fConst114 + (fConst16 * (fConst119 + (fConst116 * (fConst116 + fConst115))))));
		fConst130 = (1.0 / fConst129);
		for (int i=0; i<5; i++) fRec10[i] = 0;
		fConst131 = (0 - fConst127);
		fConst132 = (fConst16 / fConst129);
		fConst133 = tan((20106.192982974677 / double(iConst0)));
		fConst134 = (iConst0 * fConst133);
		fConst135 = sqrt((4.0 * ((iConst4 * fConst133) * fConst108)));
		fConst136 = faustpower<2>(fConst135);
		fConst137 = ((2.0 * fConst134) - (0.5 * (fConst136 / fConst134)));
		fConst138 = (fConst137 / fConst1);
		fConst139 = (11.31370849898476 * fConst138);
		fConst140 = (2.82842712474619 * fConst137);
		fConst141 = (fConst136 * fConst11);
		fConst142 = faustpower<2>(fConst137);
		fConst143 = (4 * fConst142);
		fConst144 = (fConst143 + (8 * fConst136));
		fConst145 = ((16 + (fConst16 * (fConst144 + (fConst141 * (fConst141 - fConst140))))) - fConst139);
		fConst146 = (5.65685424949238 * fConst137);
		fConst147 = (4 * fConst141);
		fConst148 = (fConst136 * fConst20);
		fConst149 = (22.62741699796952 * fConst138);
		fConst150 = ((fConst149 + (fConst148 * (fConst147 - fConst146))) - 64);
		fConst151 = ((fConst148 * (fConst146 + fConst147)) - (64 + fConst149));
		fConst152 = (8 * fConst142);
		fConst153 = (96 + (fConst16 * ((0 - (fConst152 + (16 * fConst136))) + (6 * (faustpower<4>(fConst135) * fConst16)))));
		fConst154 = (16 + (fConst139 + (fConst16 * (fConst144 + (fConst141 * (fConst141 + fConst140))))));
		fConst155 = (1.0 / fConst154);
		for (int i=0; i<5; i++) fRec11[i] = 0;
		fConst156 = (0 - fConst152);
		fConst157 = (fConst16 / fConst154);
		fConst158 = tan((40212.385965949354 / double(iConst0)));
		fConst159 = (iConst0 * fConst158);
		fConst160 = sqrt((4.0 * ((iConst4 * fConst158) * fConst133)));
		fConst161 = faustpower<2>(fConst160);
		fConst162 = ((2.0 * fConst159) - (0.5 * (fConst161 / fConst159)));
		fConst163 = (fConst162 / fConst1);
		fConst164 = (11.31370849898476 * fConst163);
		fConst165 = (2.82842712474619 * fConst162);
		fConst166 = (fConst161 * fConst11);
		fConst167 = faustpower<2>(fConst162);
		fConst168 = (4 * fConst167);
		fConst169 = (fConst168 + (8 * fConst161));
		fConst170 = ((16 + (fConst16 * (fConst169 + (fConst166 * (fConst166 - fConst165))))) - fConst164);
		fConst171 = (5.65685424949238 * fConst162);
		fConst172 = (4 * fConst166);
		fConst173 = (fConst161 * fConst20);
		fConst174 = (22.62741699796952 * fConst163);
		fConst175 = ((fConst174 + (fConst173 * (fConst172 - fConst171))) - 64);
		fConst176 = ((fConst173 * (fConst171 + fConst172)) - (64 + fConst174));
		fConst177 = (8 * fConst167);
		fConst178 = (96 + (fConst16 * ((0 - (fConst177 + (16 * fConst161))) + (6 * (faustpower<4>(fConst160) * fConst16)))));
		fConst179 = (16 + (fConst164 + (fConst16 * (fConst169 + (fConst166 * (fConst166 + fConst165))))));
		fConst180 = (1.0 / fConst179);
		for (int i=0; i<5; i++) fRec12[i] = 0;
		fConst181 = (0 - fConst177);
		fConst182 = (fConst16 / fConst179);
		fConst183 = tan((138544.23602330987 / double(iConst0)));
		fConst184 = (iConst0 * fConst183);
		fConst185 = sqrt((4.0 * ((iConst4 * fConst183) * fConst158)));
		fConst186 = faustpower<2>(fConst185);
		fConst187 = ((2.0 * fConst184) - (0.5 * (fConst186 / fConst184)));
		fConst188 = (fConst187 / fConst1);
		fConst189 = (11.31370849898476 * fConst188);
		fConst190 = (2.82842712474619 * fConst187);
		fConst191 = (fConst186 * fConst11);
		fConst192 = faustpower<2>(fConst187);
		fConst193 = (4 * fConst192);
		fConst194 = (fConst193 + (8 * fConst186));
		fConst195 = ((16 + (fConst16 * (fConst194 + (fConst191 * (fConst191 - fConst190))))) - fConst189);
		fConst196 = (5.65685424949238 * fConst187);
		fConst197 = (4 * fConst191);
		fConst198 = (fConst186 * fConst20);
		fConst199 = (22.62741699796952 * fConst188);
		fConst200 = ((fConst199 + (fConst198 * (fConst197 - fConst196))) - 64);
		fConst201 = ((fConst198 * (fConst196 + fConst197)) - (64 + fConst199));
		fConst202 = (8 * fConst192);
		fConst203 = (96 + (fConst16 * ((0 - (fConst202 + (16 * fConst186))) + (6 * (faustpower<4>(fConst185) * fConst16)))));
		fConst204 = (16 + (fConst189 + (fConst16 * (fConst194 + (fConst191 * (fConst191 + fConst190))))));
		fConst205 = (1.0 / fConst204);
		for (int i=0; i<5; i++) fRec13[i] = 0;
		fConst206 = (0 - fConst202);
		fConst207 = (fConst16 / fConst204);
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
		interface->addHorizontalSlider("LFOspeedS", &fslider0, 2.0, 0.01, 1e+01, 0.001);
		interface->addHorizontalSlider("frqminD", &fslider1, 2.0, 0.1, 5e+01, 0.1);
		interface->addHorizontalSlider("gainD", &fslider4, 1.0, 0.1, 1.9, 0.01);
		interface->addHorizontalSlider("gainS", &fslider5, 1.0, 0.1, 1.9, 0.01);
		interface->addHorizontalSlider("ratioS", &fslider2, 2.0, 0.1, 5.0, 0.01);
		interface->addHorizontalSlider("widthS", &fslider3, 5e+01, 0.0, 1e+02, 1.0);
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		double 	fSlow0 = (fConst29 * double(fslider0));
		double 	fSlow1 = cos(fSlow0);
		double 	fSlow2 = sin(fSlow0);
		double 	fSlow3 = (0 - fSlow2);
		double 	fSlow4 = (6.283185307179586 * double(fslider1));
		double 	fSlow5 = (0.5 * (628.3185307179587 - fSlow4));
		double 	fSlow6 = (fConst30 * double(fslider2));
		double 	fSlow7 = exp((fConst30 * (0 - (3.141592653589793 * double(fslider3)))));
		double 	fSlow8 = (0 - (2 * fSlow7));
		double 	fSlow9 = faustpower<2>(fSlow7);
		double 	fSlow10 = double(fslider4);
		double 	fSlow11 = double(fslider5);
		double 	fSlow12 = (0.5 * fSlow10);
		double 	fSlow13 = (0.5 * fSlow11);
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
			iVec0[0] = 1;
			double fTemp0 = (double)input0[i];
			fRec3[0] = ((fSlow2 * fRec4[1]) + (fSlow1 * fRec3[1]));
			fRec4[0] = ((1 + ((fSlow1 * fRec4[1]) + (fSlow3 * fRec3[1]))) - iVec0[1]);
			double fTemp1 = cos((fSlow6 * (fSlow4 + (fSlow5 * (1 - fRec4[0])))));
			double fTemp2 = (fSlow8 * (fTemp1 * fRec2[1]));
			double fTemp3 = (double)input1[i];
			fRec2[0] = (0 - (((fSlow9 * fRec2[2]) + (fTemp3 + fTemp2)) - fTemp0));
			double 	fRec1 = ((fSlow9 * fRec2[0]) + (fTemp2 + fRec2[2]));
			double fTemp4 = ((fTemp0 - fTemp3) + fRec1);
			double fTemp5 = (fTemp0 + fTemp3);
			double fTemp6 = (fSlow8 * (fRec6[1] * fTemp1));
			fRec6[0] = (0 - ((fTemp6 + (fSlow9 * fRec6[2])) - fTemp5));
			double 	fRec5 = ((fSlow9 * fRec6[0]) + (fTemp6 + fRec6[2]));
			double fTemp7 = (fTemp5 + fRec5);
			double fTemp8 = (0.35 * ((fSlow11 * fTemp7) + (fSlow10 * fTemp4)));
			fRec0[0] = (fTemp8 - (fConst28 * ((((fConst26 * fRec0[2]) + (fConst24 * fRec0[1])) + (fConst23 * fRec0[3])) + (fConst17 * fRec0[4]))));
			output0[i] = (FAUSTFLOAT)(fConst32 * (((fConst31 * fRec0[2]) + (fConst14 * fRec0[0])) + (fConst14 * fRec0[4])));
			fRec7[0] = (fTemp8 - (fConst55 * ((((fConst53 * fRec7[2]) + (fConst51 * fRec7[1])) + (fConst50 * fRec7[3])) + (fConst45 * fRec7[4]))));
			output1[i] = (FAUSTFLOAT)(fConst57 * (((fConst43 * fRec7[0]) + (fConst56 * fRec7[2])) + (fConst43 * fRec7[4])));
			fRec8[0] = (fTemp8 - (fConst80 * ((((fConst78 * fRec8[2]) + (fConst76 * fRec8[1])) + (fConst75 * fRec8[3])) + (fConst70 * fRec8[4]))));
			output2[i] = (FAUSTFLOAT)(fConst82 * (((fConst68 * fRec8[0]) + (fConst81 * fRec8[2])) + (fConst68 * fRec8[4])));
			fRec9[0] = (fTemp8 - (fConst105 * ((((fConst103 * fRec9[2]) + (fConst101 * fRec9[1])) + (fConst100 * fRec9[3])) + (fConst95 * fRec9[4]))));
			output3[i] = (FAUSTFLOAT)(fConst107 * (((fConst93 * fRec9[0]) + (fConst106 * fRec9[2])) + (fConst93 * fRec9[4])));
			fRec10[0] = (fTemp8 - (fConst130 * ((((fConst128 * fRec10[2]) + (fConst126 * fRec10[1])) + (fConst125 * fRec10[3])) + (fConst120 * fRec10[4]))));
			output4[i] = (FAUSTFLOAT)(fConst132 * (((fConst118 * fRec10[0]) + (fConst131 * fRec10[2])) + (fConst118 * fRec10[4])));
			fRec11[0] = (fTemp8 - (fConst155 * ((((fConst153 * fRec11[2]) + (fConst151 * fRec11[1])) + (fConst150 * fRec11[3])) + (fConst145 * fRec11[4]))));
			output5[i] = (FAUSTFLOAT)(fConst157 * (((fConst143 * fRec11[0]) + (fConst156 * fRec11[2])) + (fConst143 * fRec11[4])));
			fRec12[0] = (fTemp8 - (fConst180 * ((((fConst178 * fRec12[2]) + (fConst176 * fRec12[1])) + (fConst175 * fRec12[3])) + (fConst170 * fRec12[4]))));
			output6[i] = (FAUSTFLOAT)(fConst182 * (((fConst168 * fRec12[0]) + (fConst181 * fRec12[2])) + (fConst168 * fRec12[4])));
			fRec13[0] = (fTemp8 - (fConst205 * ((((fConst203 * fRec13[2]) + (fConst201 * fRec13[1])) + (fConst200 * fRec13[3])) + (fConst195 * fRec13[4]))));
			output7[i] = (FAUSTFLOAT)(fConst207 * (((fConst193 * fRec13[0]) + (fConst206 * fRec13[2])) + (fConst193 * fRec13[4])));
			double fTemp9 = (0.7 * ((fSlow13 * fTemp7) - (fSlow12 * fTemp4)));
			fRec14[0] = (fTemp9 - (fConst28 * ((((fConst26 * fRec14[2]) + (fConst24 * fRec14[1])) + (fConst23 * fRec14[3])) + (fConst17 * fRec14[4]))));
			output8[i] = (FAUSTFLOAT)(fConst32 * (((fConst14 * fRec14[0]) + (fConst31 * fRec14[2])) + (fConst14 * fRec14[4])));
			fRec15[0] = (fTemp9 - (fConst55 * ((((fConst53 * fRec15[2]) + (fConst51 * fRec15[1])) + (fConst50 * fRec15[3])) + (fConst45 * fRec15[4]))));
			output9[i] = (FAUSTFLOAT)(fConst57 * (((fConst43 * fRec15[0]) + (fConst56 * fRec15[2])) + (fConst43 * fRec15[4])));
			fRec16[0] = (fTemp9 - (fConst80 * ((((fConst78 * fRec16[2]) + (fConst76 * fRec16[1])) + (fConst75 * fRec16[3])) + (fConst70 * fRec16[4]))));
			output10[i] = (FAUSTFLOAT)(fConst82 * (((fConst68 * fRec16[0]) + (fConst81 * fRec16[2])) + (fConst68 * fRec16[4])));
			fRec17[0] = (fTemp9 - (fConst105 * ((((fConst103 * fRec17[2]) + (fConst101 * fRec17[1])) + (fConst100 * fRec17[3])) + (fConst95 * fRec17[4]))));
			output11[i] = (FAUSTFLOAT)(fConst107 * (((fConst93 * fRec17[0]) + (fConst106 * fRec17[2])) + (fConst93 * fRec17[4])));
			fRec18[0] = (fTemp9 - (fConst130 * ((((fConst128 * fRec18[2]) + (fConst126 * fRec18[1])) + (fConst125 * fRec18[3])) + (fConst120 * fRec18[4]))));
			output12[i] = (FAUSTFLOAT)(fConst132 * (((fConst118 * fRec18[0]) + (fConst131 * fRec18[2])) + (fConst118 * fRec18[4])));
			fRec19[0] = (fTemp9 - (fConst155 * ((((fConst153 * fRec19[2]) + (fConst151 * fRec19[1])) + (fConst150 * fRec19[3])) + (fConst145 * fRec19[4]))));
			output13[i] = (FAUSTFLOAT)(fConst157 * (((fConst143 * fRec19[0]) + (fConst156 * fRec19[2])) + (fConst143 * fRec19[4])));
			fRec20[0] = (fTemp9 - (fConst180 * ((((fConst178 * fRec20[2]) + (fConst176 * fRec20[1])) + (fConst175 * fRec20[3])) + (fConst170 * fRec20[4]))));
			output14[i] = (FAUSTFLOAT)(fConst182 * (((fConst168 * fRec20[0]) + (fConst181 * fRec20[2])) + (fConst168 * fRec20[4])));
			fRec21[0] = (fTemp9 - (fConst205 * ((((fConst203 * fRec21[2]) + (fConst201 * fRec21[1])) + (fConst200 * fRec21[3])) + (fConst195 * fRec21[4]))));
			output15[i] = (FAUSTFLOAT)(fConst207 * (((fConst193 * fRec21[0]) + (fConst206 * fRec21[2])) + (fConst193 * fRec21[4])));
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
			fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			iVec0[1] = iVec0[0];
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




