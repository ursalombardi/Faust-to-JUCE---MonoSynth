/* ------------------------------------------------------------
name: "Ursynth"
Code generated with Faust 2.70.3 (https://faust.grame.fr)
Compilation options: -a faustMinimal.h -lang cpp -i -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#include <cmath>
#include <cstring>

/************************** BEGIN MapUI.h ******************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ***********************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>
#include <stdio.h>

/************************** BEGIN UI.h *****************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ********************************************************************/

#ifndef __UI_H__
#define __UI_H__

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ***************************************************************************/

#ifndef __export__
#define __export__

// Version as a global string
#define FAUSTVERSION "2.70.3"

// Version as separated [major,minor,patch] values
#define FAUSTMAJORVERSION 2
#define FAUSTMINORVERSION 70
#define FAUSTPATCHVERSION 3

// Use FAUST_API for code that is part of the external API but is also compiled in faust and libfaust
// Use LIBFAUST_API for code that is compiled in faust and libfaust

#ifdef _WIN32
    #pragma warning (disable: 4251)
    #ifdef FAUST_EXE
        #define FAUST_API
        #define LIBFAUST_API
    #elif FAUST_LIB
        #define FAUST_API __declspec(dllexport)
        #define LIBFAUST_API __declspec(dllexport)
    #else
        #define FAUST_API
        #define LIBFAUST_API 
    #endif
#else
    #ifdef FAUST_EXE
        #define FAUST_API
        #define LIBFAUST_API
    #else
        #define FAUST_API __attribute__((visibility("default")))
        #define LIBFAUST_API __attribute__((visibility("default")))
    #endif
#endif

#endif

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
struct FAUST_API UIReal {
    
    UIReal() {}
    virtual ~UIReal() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    // -- active widgets
    
    virtual void addButton(const char* label, REAL* zone) = 0;
    virtual void addCheckButton(const char* label, REAL* zone) = 0;
    virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
    
    // -- metadata declarations
    
    virtual void declare(REAL* /*zone*/, const char* /*key*/, const char* /*val*/) {}

    // To be used by LLVM client
    virtual int sizeOfFAUSTFLOAT() { return sizeof(FAUSTFLOAT); }
};

struct FAUST_API UI : public UIReal<FAUSTFLOAT> {
    UI() {}
    virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN PathBuilder.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __PathBuilder__
#define __PathBuilder__

#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>


/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class FAUST_API PathBuilder {

    protected:
    
        std::vector<std::string> fControlsLevel;
        std::vector<std::string> fFullPaths;
        std::map<std::string, std::string> fFull2Short;  // filled by computeShortNames()
    
        /**
         * @brief check if a character is acceptable for an ID
         *
         * @param c
         * @return true is the character is acceptable for an ID
         */
        bool isIDChar(char c) const
        {
            return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9'));
        }
    
        /**
         * @brief remove all "/0x00" parts
         *
         * @param src
         * @return modified string
         */
        std::string remove0x00(const std::string& src_aux) const
        {
            std::string src = src_aux;
            std::string from = "/0x00";
            std::string to = "";
            for (size_t pos = src.find(from); pos != std::string::npos; pos = src.find(from, pos + 1)) {
                src.replace(pos, from.length(), to);
            }
            return src;
        }
    
        /**
         * @brief replace all non ID char with '_' (one '_' may replace several non ID char)
         *
         * @param src
         * @return modified string
         */
        std::string str2ID(const std::string& src) const
        {
            std::string dst;
            bool need_underscore = false;
            for (char c : src) {
                if (isIDChar(c) || (c == '/')) {
                    if (need_underscore) {
                        dst.push_back('_');
                        need_underscore = false;
                    }
                    dst.push_back(c);
                } else {
                    need_underscore = true;
                }
            }
            return dst;
        }
    
        /**
         * @brief Keep only the last n slash-parts
         *
         * @param src
         * @param n : 1 indicates the last slash-part
         * @return modified string
         */
        std::string cut(const std::string& src, int n) const
        {
            std::string rdst;
            for (int i = int(src.length())-1; i >= 0; i--) {
                char c = src[i];
                if (c != '/') {
                    rdst.push_back(c);
                } else if (n == 1) {
                    std::string dst;
                    for (int j = int(rdst.length())-1; j >= 0; j--) {
                        dst.push_back(rdst[j]);
                    }
                    return dst;
                } else {
                    n--;
                    rdst.push_back(c);
                }
            }
            return src;
        }
    
        void addFullPath(const std::string& label) { fFullPaths.push_back(buildPath(label)); }
    
        /**
         * @brief Compute the mapping between full path and short names
         */
        void computeShortNames()
        {
            std::vector<std::string>           uniquePaths;  // all full paths transformed but made unique with a prefix
            std::map<std::string, std::string> unique2full;  // all full paths transformed but made unique with a prefix
            char num_buffer[16];
            int pnum = 0;
            
            for (const auto& s : fFullPaths) {
                // Using snprintf since Teensy does not have the std::to_string function
                snprintf(num_buffer, 16, "%d", pnum++);
                std::string u = "/P" + std::string(num_buffer) + str2ID(remove0x00(s));
                uniquePaths.push_back(u);
                unique2full[u] = s;  // remember the full path associated to a unique path
            }
        
            std::map<std::string, int> uniquePath2level;                // map path to level
            for (const auto& s : uniquePaths) uniquePath2level[s] = 1;   // we init all levels to 1
            bool have_collisions = true;
        
            while (have_collisions) {
                // compute collision list
                std::set<std::string>              collisionSet;
                std::map<std::string, std::string> short2full;
                have_collisions = false;
                for (const auto& it : uniquePath2level) {
                    std::string u = it.first;
                    int n = it.second;
                    std::string shortName = cut(u, n);
                    auto p = short2full.find(shortName);
                    if (p == short2full.end()) {
                        // no collision
                        short2full[shortName] = u;
                    } else {
                        // we have a collision, add the two paths to the collision set
                        have_collisions = true;
                        collisionSet.insert(u);
                        collisionSet.insert(p->second);
                    }
                }
                for (const auto& s : collisionSet) uniquePath2level[s]++;  // increase level of colliding path
            }
        
            for (const auto& it : uniquePath2level) {
                std::string u = it.first;
                int n = it.second;
                std::string shortName = replaceCharList(cut(u, n), {'/'}, '_');
                fFull2Short[unique2full[u]] = shortName;
            }
        }
    
        std::string replaceCharList(const std::string& str, const std::vector<char>& ch1, char ch2)
        {
            auto beg = ch1.begin();
            auto end = ch1.end();
            std::string res = str;
            for (size_t i = 0; i < str.length(); ++i) {
                if (std::find(beg, end, str[i]) != end) res[i] = ch2;
            }
            return res;
        }
     
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        // Return true for the first level of groups
        bool pushLabel(const std::string& label) { fControlsLevel.push_back(label); return fControlsLevel.size() == 1;}
    
        // Return true for the last level of groups
        bool popLabel() { fControlsLevel.pop_back(); return fControlsLevel.size() == 0; }
    
        // Return a complete path built from a label
        std::string buildPath(const std::string& label)
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res = res + fControlsLevel[i] + "/";
            }
            res += label;
            return replaceCharList(res, {' ', '#', '*', ',', '?', '[', ']', '{', '}', '(', ')'}, '_');
        }
    
        // Assuming shortnames have been built, return the shortname from a label
        std::string buildShortname(const std::string& label)
        {
            return (hasShortname()) ? fFull2Short[buildPath(label)] : "";
        }
    
        bool hasShortname() { return fFull2Short.size() > 0; }
    
};

#endif  // __PathBuilder__
/**************************  END  PathBuilder.h **************************/

/*******************************************************************************
 * MapUI : Faust User Interface.
 *
 * This class creates:
 * - a map of 'labels' and zones for each UI item.
 * - a map of unique 'shortname' (built so that they never collide) and zones for each UI item
 * - a map of complete hierarchical 'paths' and zones for each UI item
 *
 * Simple 'labels', 'shortname' and complete 'paths' (to fully discriminate between possible same
 * 'labels' at different location in the UI hierachy) can be used to access a given parameter.
 ******************************************************************************/

class FAUST_API MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
        // Shortname zone map
        std::map<std::string, FAUSTFLOAT*> fShortnameZoneMap;
    
        // Full path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        void addZoneLabel(const std::string& label, FAUSTFLOAT* zone)
        {
            std::string path = buildPath(label);
            fFullPaths.push_back(path);
            fPathZoneMap[path] = zone;
            fLabelZoneMap[label] = zone;
        }
    
    public:
        
        MapUI() {}
        virtual ~MapUI() {}
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            if (popLabel()) {
                // Shortnames can be computed when all fullnames are known
                computeShortNames();
                // Fill 'shortname' map
                for (const auto& it : fFullPaths) {
                    fShortnameZoneMap[fFull2Short[it]] = fPathZoneMap[it];
                }
            }
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addZoneLabel(label, zone);
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addZoneLabel(label, zone);
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            addZoneLabel(label, zone);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            addZoneLabel(label, zone);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            addZoneLabel(label, zone);
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            addZoneLabel(label, zone);
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            addZoneLabel(label, zone);
        }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
    
        //-------------------------------------------------------------------------------
        // Public API
        //-------------------------------------------------------------------------------
    
        /**
         * Set the param value.
         *
         * @param str - the UI parameter label/shortname/path
         * @param value - the UI parameter value
         *
         */
        void setParamValue(const std::string& str, FAUSTFLOAT value)
        {
            const auto fPathZoneMapIter = fPathZoneMap.find(str);
            if (fPathZoneMapIter != fPathZoneMap.end()) {
                *fPathZoneMapIter->second = value;
                return;
            }
            
            const auto fShortnameZoneMapIter = fShortnameZoneMap.find(str);
            if (fShortnameZoneMapIter != fShortnameZoneMap.end()) {
                *fShortnameZoneMapIter->second = value;
                return;
            }
            
            const auto fLabelZoneMapIter = fLabelZoneMap.find(str);
            if (fLabelZoneMapIter != fLabelZoneMap.end()) {
                *fLabelZoneMapIter->second = value;
                return;
            }
            
            fprintf(stderr, "ERROR : setParamValue '%s' not found\n", str.c_str());
        }
        
        /**
         * Return the param value.
         *
         * @param str - the UI parameter label/shortname/path
         *
         * @return the param value.
         */
        FAUSTFLOAT getParamValue(const std::string& str)
        {
            const auto fPathZoneMapIter = fPathZoneMap.find(str);
            if (fPathZoneMapIter != fPathZoneMap.end()) {
                return *fPathZoneMapIter->second;
            }
            
            const auto fShortnameZoneMapIter = fShortnameZoneMap.find(str);
            if (fShortnameZoneMapIter != fShortnameZoneMap.end()) {
                return *fShortnameZoneMapIter->second;
            }
            
            const auto fLabelZoneMapIter = fLabelZoneMap.find(str);
            if (fLabelZoneMapIter != fLabelZoneMap.end()) {
                return *fLabelZoneMapIter->second;
            }
            
            fprintf(stderr, "ERROR : getParamValue '%s' not found\n", str.c_str());
            return 0;
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getFullpathMap() { return fPathZoneMap; }
        std::map<std::string, FAUSTFLOAT*>& getShortnameMap() { return fShortnameZoneMap; }
        std::map<std::string, FAUSTFLOAT*>& getLabelMap() { return fLabelZoneMap; }
            
        /**
         * Return the number of parameters in the UI.
         *
         * @return the number of parameters
         */
        int getParamsCount() { return int(fPathZoneMap.size()); }
        
        /**
         * Return the param path.
         *
         * @param index - the UI parameter index
         *
         * @return the param path
         */
        std::string getParamAddress(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return "";
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamAddress1(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        /**
         * Return the param shortname.
         *
         * @param index - the UI parameter index
         *
         * @return the param shortname
         */
        std::string getParamShortname(int index)
        {
            if (index < 0 || index > int(fShortnameZoneMap.size())) {
                return "";
            } else {
                auto it = fShortnameZoneMap.begin();
                while (index-- > 0 && it++ != fShortnameZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamShortname1(int index)
        {
            if (index < 0 || index > int(fShortnameZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fShortnameZoneMap.begin();
                while (index-- > 0 && it++ != fShortnameZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        /**
         * Return the param label.
         *
         * @param index - the UI parameter index
         *
         * @return the param label
         */
        std::string getParamLabel(int index)
        {
            if (index < 0 || index > int(fLabelZoneMap.size())) {
                return "";
            } else {
                auto it = fLabelZoneMap.begin();
                while (index-- > 0 && it++ != fLabelZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamLabel1(int index)
        {
            if (index < 0 || index > int(fLabelZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fLabelZoneMap.begin();
                while (index-- > 0 && it++ != fLabelZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        /**
         * Return the param path.
         *
         * @param zone - the UI parameter memory zone
         *
         * @return the param path
         */
        std::string getParamAddress(FAUSTFLOAT* zone)
        {
            for (const auto& it : fPathZoneMap) {
                if (it.second == zone) return it.first;
            }
            return "";
        }
    
        /**
         * Return the param memory zone.
         *
         * @param zone - the UI parameter label/shortname/path
         *
         * @return the param path
         */
        FAUSTFLOAT* getParamZone(const std::string& str)
        {
            const auto fPathZoneMapIter = fPathZoneMap.find(str);
            if (fPathZoneMapIter != fPathZoneMap.end()) {
                return fPathZoneMapIter->second;
            }
            
            const auto fShortnameZoneMapIter = fShortnameZoneMap.find(str);
            if (fShortnameZoneMapIter != fShortnameZoneMap.end()) {
                return fShortnameZoneMapIter->second;
            }
            
            const auto fLabelZoneMapIter = fLabelZoneMap.find(str);
            if (fLabelZoneMapIter != fLabelZoneMap.end()) {
                return fLabelZoneMapIter->second;
            }

            return nullptr;
        }
    
        /**
         * Return the param memory zone.
         *
         * @param zone - the UI parameter index
         *
         * @return the param path
         */
        FAUSTFLOAT* getParamZone(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->second;
            }
        }
    
        static bool endsWith(const std::string& str, const std::string& end)
        {
            size_t l1 = str.length();
            size_t l2 = end.length();
            return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
        }
    
};

#endif // FAUST_MAPUI_H
/**************************  END  MapUI.h **************************/
/************************** BEGIN meta.h *******************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __meta__
#define __meta__


/**
 The base class of Meta handler to be used in dsp::metadata(Meta* m) method to retrieve (key, value) metadata.
 */
struct FAUST_API Meta {
    virtual ~Meta() {}
    virtual void declare(const char* key, const char* value) = 0;
};

#endif
/**************************  END  meta.h **************************/
/************************** BEGIN dsp.h ********************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>
#include <cstdint>


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct FAUST_API UI;
struct FAUST_API Meta;

/**
 * DSP memory manager.
 */

struct FAUST_API dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    /**
     * Inform the Memory Manager with the number of expected memory zones.
     * @param count - the number of expected memory zones
     */
    virtual void begin(size_t /*count*/) {}
    
    /**
     * Give the Memory Manager information on a given memory zone.
     * @param size - the size in bytes of the memory zone
     * @param reads - the number of Read access to the zone used to compute one frame
     * @param writes - the number of Write access to the zone used to compute one frame
     */
    virtual void info(size_t /*size*/, size_t /*reads*/, size_t /*writes*/) {}

    /**
     * Inform the Memory Manager that all memory zones have been described,
     * to possibly start a 'compute the best allocation strategy' step.
     */
    virtual void end() {}
    
    /**
     * Allocate a memory zone.
     * @param size - the memory zone size in bytes
     */
    virtual void* allocate(size_t size) = 0;
    
    /**
     * Destroy a memory zone.
     * @param ptr - the memory zone pointer to be deallocated
     */
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class FAUST_API dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Return the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceInit(int sample_rate) = 0;
    
        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (like delay lines...) but keep the control parameter values */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class FAUST_API decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = nullptr):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class, used with LLVM and Interpreter backends
 * to create DSP instances from a compiled DSP program.
 */

class FAUST_API dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        /* Return factory name */
        virtual std::string getName() = 0;
    
        /* Return factory SHA key */
        virtual std::string getSHAKey() = 0;
    
        /* Return factory expanded DSP code */
        virtual std::string getDSPCode() = 0;
    
        /* Return factory compile options */
        virtual std::string getCompileOptions() = 0;
    
        /* Get the Faust DSP factory list of library dependancies */
        virtual std::vector<std::string> getLibraryList() = 0;
    
        /* Get the list of all used includes */
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        /* Get warning messages list for a given compilation */
        virtual std::vector<std::string> getWarningMessages() = 0;
    
        /* Create a new DSP instance, to be deleted with C++ 'delete' */
        virtual dsp* createDSPInstance() = 0;
    
        /* Static tables initialization, possibly implemened in sub-classes*/
        virtual void classInit(int sample_rate) {};
    
        /* Set a custom memory manager to be used when creating instances */
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
    
        /* Return the currently set custom memory manager */
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

// Denormal handling

#if defined (__SSE__)
#include <xmmintrin.h>
#endif

class FAUST_API ScopedNoDenormals {
    
    private:
    
        intptr_t fpsr = 0;
        
        void setFpStatusRegister(intptr_t fpsr_aux) noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            asm volatile("msr fpcr, %0" : : "ri" (fpsr_aux));
        #elif defined (__SSE__)
            // The volatile keyword here is needed to workaround a bug in AppleClang 13.0
            // which aggressively optimises away the variable otherwise
            volatile uint32_t fpsr_w = static_cast<uint32_t>(fpsr_aux);
            _mm_setcsr(fpsr_w);
        #endif
        }
        
        void getFpStatusRegister() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            asm volatile("mrs %0, fpcr" : "=r" (fpsr));
        #elif defined (__SSE__)
            fpsr = static_cast<intptr_t>(_mm_getcsr());
        #endif
        }
    
    public:
    
        ScopedNoDenormals() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            intptr_t mask = (1 << 24 /* FZ */);
        #elif defined (__SSE__)
        #if defined (__SSE2__)
            intptr_t mask = 0x8040;
        #else
            intptr_t mask = 0x8000;
        #endif
        #else
            intptr_t mask = 0x0000;
        #endif
            getFpStatusRegister();
            setFpStatusRegister(fpsr | mask);
        }
        
        ~ScopedNoDenormals() noexcept
        {
            setFpStatusRegister(fpsr);
        }

};

#define AVOIDDENORMALS ScopedNoDenormals ftz_scope;

#endif

/************************** END dsp.h **************************/

// BEGIN-FAUSTDSP


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

class mydspSIG0 {
	
  private:
	
	int iVec1[2];
	int iRec7[2];
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			iVec1[l3] = 0;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			iRec7[l4] = 0;
		}
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec1[0] = 1;
			iRec7[0] = (iVec1[1] + iRec7[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * float(iRec7[0]));
			iVec1[1] = iVec1[0];
			iRec7[1] = iRec7[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

const static int imydspSIG1Wave0[1302] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1009,1013,1019,1021,1031,1033,1039,1049,1051,1061,1063,1069,1087,1091,1093,1097,1103,1109,1117,1123,1129,1151,1153,1163,1171,1181,1187,1193,1201,1213,1217,1223,1229,1231,1237,1249,1259,1277,1279,1283,1289,1291,1297,1301,1303,1307,1319,1321,1327,1361,1367,1373,1381,1399,1409,1423,1427,1429,1433,1439,1447,1451,1453,1459,1471,1481,1483,1487,1489,1493,1499,1511,1523,1531,1543,1549,1553,1559,1567,1571,1579,1583,1597,1601,1607,1609,1613,1619,1621,1627,1637,1657,1663,1667,1669,1693,1697,1699,1709,1721,1723,1733,1741,1747,1753,1759,1777,1783,1787,1789,1801,1811,1823,1831,1847,1861,1867,1871,1873,1877,1879,1889,1901,1907,1913,1931,1933,1949,1951,1973,1979,1987,1993,1997,1999,2003,2011,2017,2027,2029,2039,2053,2063,2069,2081,2083,2087,2089,2099,2111,2113,2129,2131,2137,2141,2143,2153,2161,2179,2203,2207,2213,2221,2237,2239,2243,2251,2267,2269,2273,2281,2287,2293,2297,2309,2311,2333,2339,2341,2347,2351,2357,2371,2377,2381,2383,2389,2393,2399,2411,2417,2423,2437,2441,2447,2459,2467,2473,2477,2503,2521,2531,2539,2543,2549,2551,2557,2579,2591,2593,2609,2617,2621,2633,2647,2657,2659,2663,2671,2677,2683,2687,2689,2693,2699,2707,2711,2713,2719,2729,2731,2741,2749,2753,2767,2777,2789,2791,2797,2801,2803,2819,2833,2837,2843,2851,2857,2861,2879,2887,2897,2903,2909,2917,2927,2939,2953,2957,2963,2969,2971,2999,3001,3011,3019,3023,3037,3041,3049,3061,3067,3079,3083,3089,3109,3119,3121,3137,3163,3167,3169,3181,3187,3191,3203,3209,3217,3221,3229,3251,3253,3257,3259,3271,3299,3301,3307,3313,3319,3323,3329,3331,3343,3347,3359,3361,3371,3373,3389,3391,3407,3413,3433,3449,3457,3461,3463,3467,3469,3491,3499,3511,3517,3527,3529,3533,3539,3541,3547,3557,3559,3571,3581,3583,3593,3607,3613,3617,3623,3631,3637,3643,3659,3671,3673,3677,3691,3697,3701,3709,3719,3727,3733,3739,3761,3767,3769,3779,3793,3797,3803,3821,3823,3833,3847,3851,3853,3863,3877,3881,3889,3907,3911,3917,3919,3923,3929,3931,3943,3947,3967,3989,4001,4003,4007,4013,4019,4021,4027,4049,4051,4057,4073,4079,4091,4093,4099,4111,4127,4129,4133,4139,4153,4157,4159,4177,4201,4211,4217,4219,4229,4231,4241,4243,4253,4259,4261,4271,4273,4283,4289,4297,4327,4337,4339,4349,4357,4363,4373,4391,4397,4409,4421,4423,4441,4447,4451,4457,4463,4481,4483,4493,4507,4513,4517,4519,4523,4547,4549,4561,4567,4583,4591,4597,4603,4621,4637,4639,4643,4649,4651,4657,4663,4673,4679,4691,4703,4721,4723,4729,4733,4751,4759,4783,4787,4789,4793,4799,4801,4813,4817,4831,4861,4871,4877,4889,4903,4909,4919,4931,4933,4937,4943,4951,4957,4967,4969,4973,4987,4993,4999,5003,5009,5011,5021,5023,5039,5051,5059,5077,5081,5087,5099,5101,5107,5113,5119,5147,5153,5167,5171,5179,5189,5197,5209,5227,5231,5233,5237,5261,5273,5279,5281,5297,5303,5309,5323,5333,5347,5351,5381,5387,5393,5399,5407,5413,5417,5419,5431,5437,5441,5443,5449,5471,5477,5479,5483,5501,5503,5507,5519,5521,5527,5531,5557,5563,5569,5573,5581,5591,5623,5639,5641,5647,5651,5653,5657,5659,5669,5683,5689,5693,5701,5711,5717,5737,5741,5743,5749,5779,5783,5791,5801,5807,5813,5821,5827,5839,5843,5849,5851,5857,5861,5867,5869,5879,5881,5897,5903,5923,5927,5939,5953,5981,5987,6007,6011,6029,6037,6043,6047,6053,6067,6073,6079,6089,6091,6101,6113,6121,6131,6133,6143,6151,6163,6173,6197,6199,6203,6211,6217,6221,6229,6247,6257,6263,6269,6271,6277,6287,6299,6301,6311,6317,6323,6329,6337,6343,6353,6359,6361,6367,6373,6379,6389,6397,6421,6427,6449,6451,6469,6473,6481,6491,6521,6529,6547,6551,6553,6563,6569,6571,6577,6581,6599,6607,6619,6637,6653,6659,6661,6673,6679,6689,6691,6701,6703,6709,6719,6733,6737,6761,6763,6779,6781,6791,6793,6803,6823,6827,6829,6833,6841,6857,6863,6869,6871,6883,6899,6907,6911,6917,6947,6949,6959,6961,6967,6971,6977,6983,6991,6997,7001,7013,7019,7027,7039,7043,7057,7069,7079,7103,7109,7121,7127,7129,7151,7159,7177,7187,7193,7207,7211,7213,7219,7229,7237,7243,7247,7253,7283,7297,7307,7309,7321,7331,7333,7349,7351,7369,7393,7411,7417,7433,7451,7457,7459,7477,7481,7487,7489,7499,7507,7517,7523,7529,7537,7541,7547,7549,7559,7561,7573,7577,7583,7589,7591,7603,7607,7621,7639,7643,7649,7669,7673,7681,7687,7691,7699,7703,7717,7723,7727,7741,7753,7757,7759,7789,7793,7817,7823,7829,7841,7853,7867,7873,7877,7879,7883,7901,7907,7919,7927,7933,7937,7949,7951,7963,7993,8009,8011,8017,8039,8053,8059,8069,8081,8087,8089,8093,8101,8111,8117,8123,8147,8161,8167,8171,8179,8191,8209,8219,8221,8231,8233,8237,8243,8263,8269,8273,8287,8291,8293,8297,8311,8317,8329,8353,8363,8369,8377,8387,8389,8419,8423,8429,8431,8443,8447,8461,8467,8501,8513,8521,8527,8537,8539,8543,8563,8573,8581,8597,8599,8609,8623,8627,8629,8641,8647,8663,8669,8677,8681,8689,8693,8699,8707,8713,8719,8731,8737,8741,8747,8753,8761,8779,8783,8803,8807,8819,8821,8831,8837,8839,8849,8861,8863,8867,8887,8893,8923,8929,8933,8941,8951,8963,8969,8971,8999,9001,9007,9011,9013,9029,9041,9043,9049,9059,9067,9091,9103,9109,9127,9133,9137,9151,9157,9161,9173,9181,9187,9199,9203,9209,9221,9227,9239,9241,9257,9277,9281,9283,9293,9311,9319,9323,9337,9341,9343,9349,9371,9377,9391,9397,9403,9413,9419,9421,9431,9433,9437,9439,9461,9463,9467,9473,9479,9491,9497,9511,9521,9533,9539,9547,9551,9587,9601,9613,9619,9623,9629,9631,9643,9649,9661,9677,9679,9689,9697,9719,9721,9733,9739,9743,9749,9767,9769,9781,9787,9791,9803,9811,9817,9829,9833,9839,9851,9857,9859,9871,9883,9887,9901,9907,9923,9929,9931,9941,9949,9967,9973,10007,10009,10037,10039,10061,10067,10069,10079,10091,10093,10099,10103,10111,10133,10139,10141,10151,10159,10163,10169,10177,10181,10193,10211,10223,10243,10247,10253,10259,10267,10271,10273,10289,10301,10303,10313,10321,10331,10333,10337,10343,10357,10369,10391,10399,10427,10429,10433,10453,10457,10459,10463,10477,10487,10499,10501,10513,10529,10531,10559,10567,10589,10597,10601,10607,10613,10627,10631,10639,10651,10657,10663,10667};
class mydspSIG1 {
	
  private:
	
	int imydspSIG1Wave0_idx;
	
  public:
	
	int getNumInputsmydspSIG1() {
		return 0;
	}
	int getNumOutputsmydspSIG1() {
		return 1;
	}
	
	void instanceInitmydspSIG1(int sample_rate) {
		imydspSIG1Wave0_idx = 0;
	}
	
	void fillmydspSIG1(int count, int* table) {
		for (int i2 = 0; i2 < count; i2 = i2 + 1) {
			table[i2] = imydspSIG1Wave0[imydspSIG1Wave0_idx];
			imydspSIG1Wave0_idx = (1 + imydspSIG1Wave0_idx) % 1302;
		}
	}

};

static mydspSIG1* newmydspSIG1() { return (mydspSIG1*)new mydspSIG1(); }
static void deletemydspSIG1(mydspSIG1* dsp) { delete dsp; }

static float mydsp_faustpower4_f(float value) {
	return value * value * value * value;
}
static float ftbl0mydspSIG0[65536];
static int itbl1mydspSIG1[1302];

class mydsp : public dsp {
	
 private:
	
	int iVec0[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fVslider0;
	float fRec1[2];
	float fConst3;
	FAUSTFLOAT fVslider1;
	float fRec6[2];
	FAUSTFLOAT fHslider0;
	float fRec9[2];
	float fConst4;
	float fRec8[2];
	float fRec10[2];
	FAUSTFLOAT fHslider1;
	float fRec12[2];
	float fRec13[2];
	FAUSTFLOAT fHslider2;
	float fRec15[2];
	float fConst6;
	FAUSTFLOAT fHslider3;
	float fRec21[2];
	float fRec22[2];
	float fRec20[2];
	float fRec19[2];
	float fRec18[2];
	float fRec17[2];
	float fConst7;
	float fRec16[2];
	float fRec5[2];
	float fRec4[2];
	float fRec3[2];
	float fRec2[2];
	float fRec0[2];
	FAUSTFLOAT fVslider2;
	float fRec25[2];
	FAUSTFLOAT fVslider3;
	float fRec30[2];
	float fRec29[2];
	float fRec28[2];
	float fRec27[2];
	float fRec26[2];
	float fRec24[2];
	FAUSTFLOAT fHslider4;
	float fRec31[2];
	FAUSTFLOAT fCheckbox0;
	float fRec32[2];
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	float fRec36[2];
	FAUSTFLOAT fHslider7;
	float fRec37[2];
	int IOTA0;
	FAUSTFLOAT fHslider8;
	float fRec40[2];
	float fConst8;
	float fRec38[2];
	float fRec39[2];
	FAUSTFLOAT fHslider9;
	float fRec41[2];
	float fConst9;
	float fVec2[131072];
	FAUSTFLOAT fHslider10;
	float fRec46[2];
	float fRec42[2];
	float fRec43[2];
	float fRec44[2];
	float fRec45[2];
	FAUSTFLOAT fHslider11;
	float fRec47[2];
	float fVec3[131072];
	FAUSTFLOAT fHslider12;
	float fRec61[2];
	float fRec60[2];
	float fVec4[16384];
	float fVec5[2];
	float fRec59[2];
	float fRec57[2];
	float fRec63[2];
	float fVec6[16384];
	float fVec7[2];
	float fRec62[2];
	float fRec58[2];
	float fVec8[16384];
	float fRec64[2];
	float fVec9[2];
	float fRec56[2];
	float fRec54[2];
	float fRec66[2];
	float fVec10[16384];
	float fVec11[2];
	float fRec65[2];
	float fRec55[2];
	float fVec12[16384];
	float fRec67[2];
	float fVec13[2];
	float fRec53[2];
	float fRec51[2];
	float fRec69[2];
	float fVec14[16384];
	float fVec15[2];
	float fRec68[2];
	float fRec52[2];
	float fVec16[16384];
	float fRec70[2];
	float fVec17[2];
	float fRec50[2];
	float fRec48[2];
	float fRec72[2];
	float fVec18[16384];
	float fVec19[2];
	float fRec71[2];
	float fRec49[2];
	float fRec85[2];
	float fVec20[16384];
	float fVec21[2];
	float fRec84[2];
	float fRec82[2];
	float fRec87[2];
	float fVec22[16384];
	float fVec23[2];
	float fRec86[2];
	float fRec83[2];
	float fVec24[16384];
	float fRec88[2];
	float fVec25[2];
	float fRec81[2];
	float fRec79[2];
	float fRec90[2];
	float fVec26[16384];
	float fVec27[2];
	float fRec89[2];
	float fRec80[2];
	float fVec28[16384];
	float fRec91[2];
	float fVec29[2];
	float fRec78[2];
	float fRec76[2];
	float fRec93[2];
	float fVec30[16384];
	float fVec31[2];
	float fRec92[2];
	float fRec77[2];
	float fVec32[16384];
	float fRec94[2];
	float fVec33[2];
	float fRec75[2];
	float fRec73[2];
	float fRec96[2];
	float fVec34[16384];
	float fVec35[2];
	float fRec95[2];
	float fRec74[2];
	float fRec109[2];
	float fVec36[16384];
	float fVec37[2];
	float fRec108[2];
	float fRec106[2];
	float fRec111[2];
	float fVec38[16384];
	float fVec39[2];
	float fRec110[2];
	float fRec107[2];
	float fVec40[16384];
	float fRec112[2];
	float fVec41[2];
	float fRec105[2];
	float fRec103[2];
	float fRec114[2];
	float fVec42[16384];
	float fVec43[2];
	float fRec113[2];
	float fRec104[2];
	float fVec44[16384];
	float fRec115[2];
	float fVec45[2];
	float fRec102[2];
	float fRec100[2];
	float fRec117[2];
	float fVec46[16384];
	float fVec47[2];
	float fRec116[2];
	float fRec101[2];
	float fVec48[16384];
	float fRec118[2];
	float fVec49[2];
	float fRec99[2];
	float fRec97[2];
	float fRec120[2];
	float fVec50[16384];
	float fVec51[2];
	float fRec119[2];
	float fRec98[2];
	float fRec35[2];
	float fRec33[1024];
	float fRec121[2];
	float fRec34[1024];
	
 public:
	mydsp() {}

	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/tabulateNd", "Copyright (C) 2023 Bart Brouns <bart@magnetophon.nl>");
		m->declare("basics.lib/version", "1.12.0");
		m->declare("compile_options", "-a faustMinimal.h -lang cpp -i -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("delays.lib/fdelay1a:author", "Julius O. Smith III");
		m->declare("delays.lib/fdelay4:author", "Julius O. Smith III");
		m->declare("delays.lib/fdelayltv:author", "Julius O. Smith III");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.1.0");
		m->declare("filename", "Ursynth.dsp");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/nlf2:author", "Julius O. Smith III");
		m->declare("filters.lib/nlf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/nlf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.3.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.7.0");
		m->declare("misceffects.lib/dryWetMixer:author", "David Braun, revised by Stéphane Letz");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.4.0");
		m->declare("name", "Ursynth");
		m->declare("options", "[midi:on][nvoices:12]");
		m->declare("oscillators.lib/CZpulse:author", "Bart Brouns");
		m->declare("oscillators.lib/CZpulse:licence", "STK-4.3");
		m->declare("oscillators.lib/CZsaw:author", "Bart Brouns");
		m->declare("oscillators.lib/CZsaw:licence", "STK-4.3");
		m->declare("oscillators.lib/CZsquare:author", "Bart Brouns");
		m->declare("oscillators.lib/CZsquare:licence", "STK-4.3");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/saw2ptr:author", "Julius O. Smith III");
		m->declare("oscillators.lib/saw2ptr:license", "STK-4.3");
		m->declare("oscillators.lib/version", "1.5.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("reverbs.lib/greyhole:author", "Julian Parker, bug fixes and minor interface changes by Till Bovermann");
		m->declare("reverbs.lib/greyhole:license", "GPL2+");
		m->declare("reverbs.lib/name", "Faust Reverb Library");
		m->declare("reverbs.lib/version", "1.2.1");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.5.0");
		m->declare("vaeffects.lib/moog_vcf:author", "Julius O. Smith III");
		m->declare("vaeffects.lib/moog_vcf:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("vaeffects.lib/moog_vcf:license", "MIT-style STK-4.3 license");
		m->declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m->declare("vaeffects.lib/version", "1.2.1");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
		mydspSIG1* sig1 = newmydspSIG1();
		sig1->instanceInitmydspSIG1(sample_rate);
		sig1->fillmydspSIG1(1302, itbl1mydspSIG1);
		deletemydspSIG0(sig0);
		deletemydspSIG1(sig1);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 6.2831855f / fConst0;
		fConst4 = 1.0f / fConst0;
		float fConst5 = 5.0265484f / fConst0;
		fConst6 = 1.0f - fConst5;
		fConst7 = mydsp_faustpower4_f(fConst5);
		fConst8 = 3.1415927f / fConst0;
		fConst9 = 0.00056689343f * fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(2e+03f);
		fVslider1 = FAUSTFLOAT(0.5f);
		fHslider0 = FAUSTFLOAT(2e+02f);
		fHslider1 = FAUSTFLOAT(0.2f);
		fHslider2 = FAUSTFLOAT(0.65f);
		fHslider3 = FAUSTFLOAT(0.95f);
		fVslider2 = FAUSTFLOAT(2e+02f);
		fVslider3 = FAUSTFLOAT(0.7f);
		fHslider4 = FAUSTFLOAT(0.5f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(1.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(0.5f);
		fHslider8 = FAUSTFLOAT(1.0f);
		fHslider9 = FAUSTFLOAT(0.0f);
		fHslider10 = FAUSTFLOAT(0.1f);
		fHslider11 = FAUSTFLOAT(0.5f);
		fHslider12 = FAUSTFLOAT(1.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec6[l2] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec9[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec8[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec10[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec12[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec13[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec15[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec21[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec22[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec20[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec19[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec18[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec17[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec16[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec5[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec4[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec3[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fRec2[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fRec0[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec25[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fRec30[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec29[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			fRec28[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec27[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			fRec26[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec24[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			fRec31[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec32[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 2; l32 = l32 + 1) {
			fRec36[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fRec37[l33] = 0.0f;
		}
		IOTA0 = 0;
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			fRec40[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			fRec38[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 2; l36 = l36 + 1) {
			fRec39[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec41[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 131072; l38 = l38 + 1) {
			fVec2[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			fRec46[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			fRec42[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			fRec43[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 2; l42 = l42 + 1) {
			fRec44[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec45[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 2; l44 = l44 + 1) {
			fRec47[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 131072; l45 = l45 + 1) {
			fVec3[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 2; l46 = l46 + 1) {
			fRec61[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 2; l47 = l47 + 1) {
			fRec60[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 16384; l48 = l48 + 1) {
			fVec4[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 2; l49 = l49 + 1) {
			fVec5[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 2; l50 = l50 + 1) {
			fRec59[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 2; l51 = l51 + 1) {
			fRec57[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 2; l52 = l52 + 1) {
			fRec63[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 16384; l53 = l53 + 1) {
			fVec6[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 2; l54 = l54 + 1) {
			fVec7[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 2; l55 = l55 + 1) {
			fRec62[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 2; l56 = l56 + 1) {
			fRec58[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 16384; l57 = l57 + 1) {
			fVec8[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 2; l58 = l58 + 1) {
			fRec64[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 2; l59 = l59 + 1) {
			fVec9[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 2; l60 = l60 + 1) {
			fRec56[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 2; l61 = l61 + 1) {
			fRec54[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 2; l62 = l62 + 1) {
			fRec66[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 16384; l63 = l63 + 1) {
			fVec10[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 2; l64 = l64 + 1) {
			fVec11[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 2; l65 = l65 + 1) {
			fRec65[l65] = 0.0f;
		}
		for (int l66 = 0; l66 < 2; l66 = l66 + 1) {
			fRec55[l66] = 0.0f;
		}
		for (int l67 = 0; l67 < 16384; l67 = l67 + 1) {
			fVec12[l67] = 0.0f;
		}
		for (int l68 = 0; l68 < 2; l68 = l68 + 1) {
			fRec67[l68] = 0.0f;
		}
		for (int l69 = 0; l69 < 2; l69 = l69 + 1) {
			fVec13[l69] = 0.0f;
		}
		for (int l70 = 0; l70 < 2; l70 = l70 + 1) {
			fRec53[l70] = 0.0f;
		}
		for (int l71 = 0; l71 < 2; l71 = l71 + 1) {
			fRec51[l71] = 0.0f;
		}
		for (int l72 = 0; l72 < 2; l72 = l72 + 1) {
			fRec69[l72] = 0.0f;
		}
		for (int l73 = 0; l73 < 16384; l73 = l73 + 1) {
			fVec14[l73] = 0.0f;
		}
		for (int l74 = 0; l74 < 2; l74 = l74 + 1) {
			fVec15[l74] = 0.0f;
		}
		for (int l75 = 0; l75 < 2; l75 = l75 + 1) {
			fRec68[l75] = 0.0f;
		}
		for (int l76 = 0; l76 < 2; l76 = l76 + 1) {
			fRec52[l76] = 0.0f;
		}
		for (int l77 = 0; l77 < 16384; l77 = l77 + 1) {
			fVec16[l77] = 0.0f;
		}
		for (int l78 = 0; l78 < 2; l78 = l78 + 1) {
			fRec70[l78] = 0.0f;
		}
		for (int l79 = 0; l79 < 2; l79 = l79 + 1) {
			fVec17[l79] = 0.0f;
		}
		for (int l80 = 0; l80 < 2; l80 = l80 + 1) {
			fRec50[l80] = 0.0f;
		}
		for (int l81 = 0; l81 < 2; l81 = l81 + 1) {
			fRec48[l81] = 0.0f;
		}
		for (int l82 = 0; l82 < 2; l82 = l82 + 1) {
			fRec72[l82] = 0.0f;
		}
		for (int l83 = 0; l83 < 16384; l83 = l83 + 1) {
			fVec18[l83] = 0.0f;
		}
		for (int l84 = 0; l84 < 2; l84 = l84 + 1) {
			fVec19[l84] = 0.0f;
		}
		for (int l85 = 0; l85 < 2; l85 = l85 + 1) {
			fRec71[l85] = 0.0f;
		}
		for (int l86 = 0; l86 < 2; l86 = l86 + 1) {
			fRec49[l86] = 0.0f;
		}
		for (int l87 = 0; l87 < 2; l87 = l87 + 1) {
			fRec85[l87] = 0.0f;
		}
		for (int l88 = 0; l88 < 16384; l88 = l88 + 1) {
			fVec20[l88] = 0.0f;
		}
		for (int l89 = 0; l89 < 2; l89 = l89 + 1) {
			fVec21[l89] = 0.0f;
		}
		for (int l90 = 0; l90 < 2; l90 = l90 + 1) {
			fRec84[l90] = 0.0f;
		}
		for (int l91 = 0; l91 < 2; l91 = l91 + 1) {
			fRec82[l91] = 0.0f;
		}
		for (int l92 = 0; l92 < 2; l92 = l92 + 1) {
			fRec87[l92] = 0.0f;
		}
		for (int l93 = 0; l93 < 16384; l93 = l93 + 1) {
			fVec22[l93] = 0.0f;
		}
		for (int l94 = 0; l94 < 2; l94 = l94 + 1) {
			fVec23[l94] = 0.0f;
		}
		for (int l95 = 0; l95 < 2; l95 = l95 + 1) {
			fRec86[l95] = 0.0f;
		}
		for (int l96 = 0; l96 < 2; l96 = l96 + 1) {
			fRec83[l96] = 0.0f;
		}
		for (int l97 = 0; l97 < 16384; l97 = l97 + 1) {
			fVec24[l97] = 0.0f;
		}
		for (int l98 = 0; l98 < 2; l98 = l98 + 1) {
			fRec88[l98] = 0.0f;
		}
		for (int l99 = 0; l99 < 2; l99 = l99 + 1) {
			fVec25[l99] = 0.0f;
		}
		for (int l100 = 0; l100 < 2; l100 = l100 + 1) {
			fRec81[l100] = 0.0f;
		}
		for (int l101 = 0; l101 < 2; l101 = l101 + 1) {
			fRec79[l101] = 0.0f;
		}
		for (int l102 = 0; l102 < 2; l102 = l102 + 1) {
			fRec90[l102] = 0.0f;
		}
		for (int l103 = 0; l103 < 16384; l103 = l103 + 1) {
			fVec26[l103] = 0.0f;
		}
		for (int l104 = 0; l104 < 2; l104 = l104 + 1) {
			fVec27[l104] = 0.0f;
		}
		for (int l105 = 0; l105 < 2; l105 = l105 + 1) {
			fRec89[l105] = 0.0f;
		}
		for (int l106 = 0; l106 < 2; l106 = l106 + 1) {
			fRec80[l106] = 0.0f;
		}
		for (int l107 = 0; l107 < 16384; l107 = l107 + 1) {
			fVec28[l107] = 0.0f;
		}
		for (int l108 = 0; l108 < 2; l108 = l108 + 1) {
			fRec91[l108] = 0.0f;
		}
		for (int l109 = 0; l109 < 2; l109 = l109 + 1) {
			fVec29[l109] = 0.0f;
		}
		for (int l110 = 0; l110 < 2; l110 = l110 + 1) {
			fRec78[l110] = 0.0f;
		}
		for (int l111 = 0; l111 < 2; l111 = l111 + 1) {
			fRec76[l111] = 0.0f;
		}
		for (int l112 = 0; l112 < 2; l112 = l112 + 1) {
			fRec93[l112] = 0.0f;
		}
		for (int l113 = 0; l113 < 16384; l113 = l113 + 1) {
			fVec30[l113] = 0.0f;
		}
		for (int l114 = 0; l114 < 2; l114 = l114 + 1) {
			fVec31[l114] = 0.0f;
		}
		for (int l115 = 0; l115 < 2; l115 = l115 + 1) {
			fRec92[l115] = 0.0f;
		}
		for (int l116 = 0; l116 < 2; l116 = l116 + 1) {
			fRec77[l116] = 0.0f;
		}
		for (int l117 = 0; l117 < 16384; l117 = l117 + 1) {
			fVec32[l117] = 0.0f;
		}
		for (int l118 = 0; l118 < 2; l118 = l118 + 1) {
			fRec94[l118] = 0.0f;
		}
		for (int l119 = 0; l119 < 2; l119 = l119 + 1) {
			fVec33[l119] = 0.0f;
		}
		for (int l120 = 0; l120 < 2; l120 = l120 + 1) {
			fRec75[l120] = 0.0f;
		}
		for (int l121 = 0; l121 < 2; l121 = l121 + 1) {
			fRec73[l121] = 0.0f;
		}
		for (int l122 = 0; l122 < 2; l122 = l122 + 1) {
			fRec96[l122] = 0.0f;
		}
		for (int l123 = 0; l123 < 16384; l123 = l123 + 1) {
			fVec34[l123] = 0.0f;
		}
		for (int l124 = 0; l124 < 2; l124 = l124 + 1) {
			fVec35[l124] = 0.0f;
		}
		for (int l125 = 0; l125 < 2; l125 = l125 + 1) {
			fRec95[l125] = 0.0f;
		}
		for (int l126 = 0; l126 < 2; l126 = l126 + 1) {
			fRec74[l126] = 0.0f;
		}
		for (int l127 = 0; l127 < 2; l127 = l127 + 1) {
			fRec109[l127] = 0.0f;
		}
		for (int l128 = 0; l128 < 16384; l128 = l128 + 1) {
			fVec36[l128] = 0.0f;
		}
		for (int l129 = 0; l129 < 2; l129 = l129 + 1) {
			fVec37[l129] = 0.0f;
		}
		for (int l130 = 0; l130 < 2; l130 = l130 + 1) {
			fRec108[l130] = 0.0f;
		}
		for (int l131 = 0; l131 < 2; l131 = l131 + 1) {
			fRec106[l131] = 0.0f;
		}
		for (int l132 = 0; l132 < 2; l132 = l132 + 1) {
			fRec111[l132] = 0.0f;
		}
		for (int l133 = 0; l133 < 16384; l133 = l133 + 1) {
			fVec38[l133] = 0.0f;
		}
		for (int l134 = 0; l134 < 2; l134 = l134 + 1) {
			fVec39[l134] = 0.0f;
		}
		for (int l135 = 0; l135 < 2; l135 = l135 + 1) {
			fRec110[l135] = 0.0f;
		}
		for (int l136 = 0; l136 < 2; l136 = l136 + 1) {
			fRec107[l136] = 0.0f;
		}
		for (int l137 = 0; l137 < 16384; l137 = l137 + 1) {
			fVec40[l137] = 0.0f;
		}
		for (int l138 = 0; l138 < 2; l138 = l138 + 1) {
			fRec112[l138] = 0.0f;
		}
		for (int l139 = 0; l139 < 2; l139 = l139 + 1) {
			fVec41[l139] = 0.0f;
		}
		for (int l140 = 0; l140 < 2; l140 = l140 + 1) {
			fRec105[l140] = 0.0f;
		}
		for (int l141 = 0; l141 < 2; l141 = l141 + 1) {
			fRec103[l141] = 0.0f;
		}
		for (int l142 = 0; l142 < 2; l142 = l142 + 1) {
			fRec114[l142] = 0.0f;
		}
		for (int l143 = 0; l143 < 16384; l143 = l143 + 1) {
			fVec42[l143] = 0.0f;
		}
		for (int l144 = 0; l144 < 2; l144 = l144 + 1) {
			fVec43[l144] = 0.0f;
		}
		for (int l145 = 0; l145 < 2; l145 = l145 + 1) {
			fRec113[l145] = 0.0f;
		}
		for (int l146 = 0; l146 < 2; l146 = l146 + 1) {
			fRec104[l146] = 0.0f;
		}
		for (int l147 = 0; l147 < 16384; l147 = l147 + 1) {
			fVec44[l147] = 0.0f;
		}
		for (int l148 = 0; l148 < 2; l148 = l148 + 1) {
			fRec115[l148] = 0.0f;
		}
		for (int l149 = 0; l149 < 2; l149 = l149 + 1) {
			fVec45[l149] = 0.0f;
		}
		for (int l150 = 0; l150 < 2; l150 = l150 + 1) {
			fRec102[l150] = 0.0f;
		}
		for (int l151 = 0; l151 < 2; l151 = l151 + 1) {
			fRec100[l151] = 0.0f;
		}
		for (int l152 = 0; l152 < 2; l152 = l152 + 1) {
			fRec117[l152] = 0.0f;
		}
		for (int l153 = 0; l153 < 16384; l153 = l153 + 1) {
			fVec46[l153] = 0.0f;
		}
		for (int l154 = 0; l154 < 2; l154 = l154 + 1) {
			fVec47[l154] = 0.0f;
		}
		for (int l155 = 0; l155 < 2; l155 = l155 + 1) {
			fRec116[l155] = 0.0f;
		}
		for (int l156 = 0; l156 < 2; l156 = l156 + 1) {
			fRec101[l156] = 0.0f;
		}
		for (int l157 = 0; l157 < 16384; l157 = l157 + 1) {
			fVec48[l157] = 0.0f;
		}
		for (int l158 = 0; l158 < 2; l158 = l158 + 1) {
			fRec118[l158] = 0.0f;
		}
		for (int l159 = 0; l159 < 2; l159 = l159 + 1) {
			fVec49[l159] = 0.0f;
		}
		for (int l160 = 0; l160 < 2; l160 = l160 + 1) {
			fRec99[l160] = 0.0f;
		}
		for (int l161 = 0; l161 < 2; l161 = l161 + 1) {
			fRec97[l161] = 0.0f;
		}
		for (int l162 = 0; l162 < 2; l162 = l162 + 1) {
			fRec120[l162] = 0.0f;
		}
		for (int l163 = 0; l163 < 16384; l163 = l163 + 1) {
			fVec50[l163] = 0.0f;
		}
		for (int l164 = 0; l164 < 2; l164 = l164 + 1) {
			fVec51[l164] = 0.0f;
		}
		for (int l165 = 0; l165 < 2; l165 = l165 + 1) {
			fRec119[l165] = 0.0f;
		}
		for (int l166 = 0; l166 < 2; l166 = l166 + 1) {
			fRec98[l166] = 0.0f;
		}
		for (int l167 = 0; l167 < 2; l167 = l167 + 1) {
			fRec35[l167] = 0.0f;
		}
		for (int l168 = 0; l168 < 1024; l168 = l168 + 1) {
			fRec33[l168] = 0.0f;
		}
		for (int l169 = 0; l169 < 2; l169 = l169 + 1) {
			fRec121[l169] = 0.0f;
		}
		for (int l170 = 0; l170 < 1024; l170 = l170 + 1) {
			fRec34[l170] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Ursynth");
		ui_interface->openHorizontalBox("every");
		ui_interface->openVerticalBox("Basic");
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->addHorizontalSlider("freq", &fHslider0, FAUSTFLOAT(2e+02f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+03f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->addHorizontalSlider("gain", &fHslider5, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider2, "3", "");
		ui_interface->addHorizontalSlider("index", &fHslider2, FAUSTFLOAT(0.65f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider3, "3", "");
		ui_interface->addHorizontalSlider("index2", &fHslider3, FAUSTFLOAT(0.95f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider1, "3", "");
		ui_interface->addHorizontalSlider("index3", &fHslider1, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fCheckbox0, "4", "");
		ui_interface->addCheckButton("gate", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("moog");
		ui_interface->addVerticalSlider("fr", &fVslider2, FAUSTFLOAT(2e+02f), FAUSTFLOAT(2e+02f), FAUSTFLOAT(4e+03f), FAUSTFLOAT(0.001f));
		ui_interface->addVerticalSlider("fr2", &fVslider0, FAUSTFLOAT(2e+03f), FAUSTFLOAT(2e+02f), FAUSTFLOAT(4e+03f), FAUSTFLOAT(0.001f));
		ui_interface->addVerticalSlider("res", &fVslider3, FAUSTFLOAT(0.7f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->addVerticalSlider("res2", &fVslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("damp", &fHslider6, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("dt", &fHslider10, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.1f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("earlydiff", &fHslider11, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("feedback", &fHslider7, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("moddepth", &fHslider9, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("modfreq", &fHslider8, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("size", &fHslider12, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.5f), FAUSTFLOAT(3.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("wetdrymix", &fHslider4, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst1 * float(fVslider0);
		float fSlow1 = fConst1 * float(fVslider1);
		float fSlow2 = fConst1 * float(fHslider0);
		float fSlow3 = fConst1 * float(fHslider1);
		float fSlow4 = fConst1 * float(fHslider2);
		float fSlow5 = fConst1 * float(fHslider3);
		float fSlow6 = fConst1 * float(fVslider2);
		float fSlow7 = fConst1 * float(fVslider3);
		float fSlow8 = fConst1 * float(fHslider4);
		float fSlow9 = fConst1 * float(fCheckbox0);
		float fSlow10 = float(fHslider5);
		float fSlow11 = 0.5f * fSlow10;
		float fSlow12 = fConst1 * float(fHslider6);
		float fSlow13 = fConst1 * float(fHslider7);
		float fSlow14 = fConst1 * float(fHslider8);
		float fSlow15 = fConst1 * float(fHslider9);
		float fSlow16 = fConst1 * float(fHslider10);
		float fSlow17 = fConst1 * float(fHslider11);
		float fSlow18 = fConst1 * float(fHslider12);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			fRec1[0] = fSlow0 + fConst2 * fRec1[1];
			float fTemp0 = fConst3 * fRec1[0];
			float fTemp1 = 1.0f - fTemp0;
			fRec6[0] = fSlow1 + fConst2 * fRec6[1];
			int iTemp2 = 1 - iVec0[1];
			fRec9[0] = fSlow2 + fConst2 * fRec9[1];
			float fTemp3 = ((iTemp2) ? 0.0f : fRec8[1] + fConst4 * fRec9[0]);
			fRec8[0] = fTemp3 - std::floor(fTemp3);
			float fTemp4 = ftbl0mydspSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec8[0]), 65535))];
			float fTemp5 = std::max<float>(1.1920929e-07f, std::fabs(1.0050251f * fRec9[0]));
			float fTemp6 = fConst4 * fTemp5;
			float fTemp7 = fRec10[1] + fTemp6;
			float fTemp8 = fTemp7 + -1.0f;
			int iTemp9 = fTemp8 < 0.0f;
			fRec10[0] = ((iTemp9) ? fTemp7 : fTemp8);
			float fRec11 = ((iTemp9) ? fTemp7 : fRec10[1] + fTemp6 + fTemp8 * (1.0f - fConst0 / fTemp5));
			float fTemp10 = 2.0f * fRec11;
			float fTemp11 = fTemp10 + -1.0f;
			fRec12[0] = fSlow3 + fConst2 * fRec12[1];
			float fTemp12 = std::max<float>(0.0f, std::min<float>(0.99f, fRec12[0]));
			float fTemp13 = std::max<float>(1.1920929e-07f, std::fabs(0.9876543f * fRec9[0]));
			float fTemp14 = fConst4 * fTemp13;
			float fTemp15 = fRec13[1] + fTemp14;
			float fTemp16 = fTemp15 + -1.0f;
			int iTemp17 = fTemp16 < 0.0f;
			fRec13[0] = ((iTemp17) ? fTemp15 : fTemp16);
			float fRec14 = ((iTemp17) ? fTemp15 : fRec13[1] + fTemp14 + fTemp16 * (1.0f - fConst0 / fTemp13));
			float fTemp18 = 2.0f * fRec14 + -1.0f;
			float fTemp19 = 2.0f * fTemp18;
			float fTemp20 = std::floor(fTemp19 + 1.0f);
			float fTemp21 = fTemp19 + (1.0f - fTemp20);
			fRec15[0] = fSlow4 + fConst2 * fRec15[1];
			float fTemp22 = std::min<float>(1.0f, std::max<float>(0.0f, std::sqrt(std::sqrt(fRec15[0]))));
			fRec21[0] = fSlow5 + fConst2 * fRec21[1];
			float fTemp23 = std::min<float>(0.5f, std::max<float>(0.01f, 0.5f * (1.0f - fRec21[0])));
			float fTemp24 = 0.5f - fTemp23;
			float fTemp25 = std::max<float>(1.1920929e-07f, std::fabs(0.99502486f * fRec9[0]));
			float fTemp26 = fConst4 * fTemp25;
			float fTemp27 = fRec22[1] + fTemp26;
			float fTemp28 = fTemp27 + -1.0f;
			int iTemp29 = fTemp28 < 0.0f;
			fRec22[0] = ((iTemp29) ? fTemp27 : fTemp28);
			float fRec23 = ((iTemp29) ? fTemp27 : fRec22[1] + fTemp26 + fTemp28 * (1.0f - fConst0 / fTemp25));
			float fTemp30 = 2.0f * fRec23;
			float fTemp31 = fTemp30 + -1.0f;
			fRec20[0] = fConst6 * fRec20[1] + std::cos(6.2831855f * (fTemp30 + std::min<float>(fTemp31 * fTemp24 / fTemp23, fTemp24 * (1.0f - fTemp31) / (1.0f - fTemp23)) + -1.0f)) - 3.999996f * fRec16[1];
			fRec19[0] = fRec20[0] + fConst6 * fRec19[1];
			fRec18[0] = fRec19[0] + fConst6 * fRec18[1];
			fRec17[0] = fRec18[0] + fConst6 * fRec17[1];
			fRec16[0] = fConst7 * fRec17[0];
			float fTemp32 = 0.25f * (fRec16[0] + std::cos(3.1415927f * (float(fTemp18 >= 0.5f) + fTemp19 + (1.0f - (fTemp20 + std::min<float>(fTemp21, fTemp22 * (1.0f - fTemp21) / (1.0f - fTemp22)))))) + std::cos(6.2831855f * (fTemp10 + (-1.0f - std::min<float>(fTemp11, fTemp12 * (1.0f - fTemp11) / (1.0f - fTemp12))))));
			fRec5[0] = fTemp32 + fTemp4 + fTemp1 * fRec5[1] - 4.0f * std::max<float>(0.0f, std::min<float>(fRec6[0], 0.999999f)) * fRec0[1];
			fRec4[0] = fRec5[0] + fTemp1 * fRec4[1];
			fRec3[0] = fRec4[0] + fTemp1 * fRec3[1];
			fRec2[0] = fRec3[0] + fRec2[1] * fTemp1;
			fRec0[0] = fRec2[0] * mydsp_faustpower4_f(fTemp0);
			fRec25[0] = fSlow6 + fConst2 * fRec25[1];
			float fTemp33 = fConst3 * fRec25[0];
			float fTemp34 = 1.0f - fTemp33;
			fRec30[0] = fSlow7 + fConst2 * fRec30[1];
			fRec29[0] = fTemp32 + fTemp34 * fRec29[1] + fTemp4 - 4.0f * std::max<float>(0.0f, std::min<float>(fRec30[0], 0.999999f)) * fRec24[1];
			fRec28[0] = fRec29[0] + fTemp34 * fRec28[1];
			fRec27[0] = fRec28[0] + fTemp34 * fRec27[1];
			fRec26[0] = fRec27[0] + fRec26[1] * fTemp34;
			fRec24[0] = fRec26[0] * mydsp_faustpower4_f(fTemp33);
			float fTemp35 = fRec24[0] + 0.25f * fRec0[0];
			fRec31[0] = fSlow8 + fConst2 * fRec31[1];
			fRec32[0] = fSlow9 + fConst2 * fRec32[1];
			float fTemp36 = fSlow11 * fRec32[0] * (1.0f - fRec31[0]) * fTemp35;
			fRec36[0] = fSlow12 + fConst2 * fRec36[1];
			float fTemp37 = fRec36[0] + fRec36[1];
			float fTemp38 = fSlow10 * fRec32[0] * fTemp35;
			fRec37[0] = fSlow13 + fConst2 * fRec37[1];
			float fTemp39 = fRec37[0] + fRec37[1];
			fRec40[0] = fSlow14 + fConst2 * fRec40[1];
			float fTemp40 = fConst8 * (fRec40[0] + fRec40[1]);
			float fTemp41 = std::cos(fTemp40);
			float fTemp42 = std::sin(fTemp40);
			fRec38[0] = fRec39[1] * fTemp42 + fRec38[1] * fTemp41;
			fRec39[0] = float(iTemp2) + fRec39[1] * fTemp41 - fTemp42 * fRec38[1];
			fRec41[0] = fSlow15 + fConst2 * fRec41[1];
			float fTemp43 = fRec41[0] + fRec41[1];
			float fTemp44 = fConst9 * fTemp43 * (fRec39[0] + 1.0f);
			float fTemp45 = fTemp44 + 8.500005f;
			int iTemp46 = int(fTemp45);
			float fTemp47 = std::floor(fTemp45);
			float fTemp48 = fTemp44 + (7.0f - fTemp47);
			float fTemp49 = fTemp44 + (8.0f - fTemp47);
			float fTemp50 = fTemp44 + (9.0f - fTemp47);
			float fTemp51 = fTemp44 + (1e+01f - fTemp47);
			float fTemp52 = fTemp51 * fTemp50;
			float fTemp53 = fTemp52 * fTemp49;
			float fTemp54 = (fTemp44 + (6.0f - fTemp47)) * (fTemp48 * (fTemp49 * (0.041666668f * fRec33[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp46)) + 1)) & 1023] * fTemp50 - 0.16666667f * fTemp51 * fRec33[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp46 + 1)) + 1)) & 1023]) + 0.25f * fTemp52 * fRec33[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp46 + 2)) + 1)) & 1023]) - 0.16666667f * fTemp53 * fRec33[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp46 + 3)) + 1)) & 1023]) + 0.041666668f * fTemp53 * fTemp48 * fRec33[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp46 + 4)) + 1)) & 1023];
			fVec2[IOTA0 & 131071] = fTemp54;
			fRec46[0] = fSlow16 + fConst2 * fRec46[1];
			float fTemp55 = std::floor(std::min<float>(65533.0f, fConst0 * fRec46[0]));
			float fTemp56 = ((fRec42[1] != 0.0f) ? (((fRec43[1] > 0.0f) & (fRec43[1] < 1.0f)) ? fRec42[1] : 0.0f) : (((fRec43[1] == 0.0f) & (fTemp55 != fRec44[1])) ? 4.5351473e-05f : (((fRec43[1] == 1.0f) & (fTemp55 != fRec45[1])) ? -4.5351473e-05f : 0.0f)));
			fRec42[0] = fTemp56;
			fRec43[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec43[1] + fTemp56));
			fRec44[0] = (((fRec43[1] >= 1.0f) & (fRec45[1] != fTemp55)) ? fTemp55 : fRec44[1]);
			fRec45[0] = (((fRec43[1] <= 0.0f) & (fRec44[1] != fTemp55)) ? fTemp55 : fRec45[1]);
			int iTemp57 = int(std::min<float>(65536.0f, std::max<float>(0.0f, fRec44[0])));
			float fTemp58 = fVec2[(IOTA0 - iTemp57) & 131071];
			int iTemp59 = int(std::min<float>(65536.0f, std::max<float>(0.0f, fRec45[0])));
			float fTemp60 = (fTemp58 + fRec43[0] * (fVec2[(IOTA0 - iTemp59) & 131071] - fTemp58)) * fTemp39 + fTemp38;
			fRec47[0] = fSlow17 + fConst2 * fRec47[1];
			float fTemp61 = fRec47[0] + fRec47[1];
			float fTemp62 = 0.5f * fTemp61;
			float fTemp63 = std::sin(fTemp62);
			float fTemp64 = std::cos(fTemp62);
			float fTemp65 = fConst9 * fTemp43 * (fRec38[0] + 1.0f);
			float fTemp66 = fTemp65 + 8.500005f;
			int iTemp67 = int(fTemp66);
			float fTemp68 = std::floor(fTemp66);
			float fTemp69 = fTemp65 + (7.0f - fTemp68);
			float fTemp70 = fTemp65 + (8.0f - fTemp68);
			float fTemp71 = fTemp65 + (9.0f - fTemp68);
			float fTemp72 = fTemp65 + (1e+01f - fTemp68);
			float fTemp73 = fTemp72 * fTemp71;
			float fTemp74 = fTemp73 * fTemp70;
			float fTemp75 = (fTemp65 + (6.0f - fTemp68)) * (fTemp69 * (fTemp70 * (0.041666668f * fRec34[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp67)) + 1)) & 1023] * fTemp71 - 0.16666667f * fTemp72 * fRec34[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp67 + 1)) + 1)) & 1023]) + 0.25f * fTemp73 * fRec34[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp67 + 2)) + 1)) & 1023]) - 0.16666667f * fTemp74 * fRec34[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp67 + 3)) + 1)) & 1023]) + 0.041666668f * fTemp74 * fTemp69 * fRec34[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp67 + 4)) + 1)) & 1023];
			fVec3[IOTA0 & 131071] = fTemp75;
			float fTemp76 = fVec3[(IOTA0 - iTemp57) & 131071];
			float fTemp77 = fTemp38 + fTemp39 * (fTemp76 + fRec43[0] * (fVec3[(IOTA0 - iTemp59) & 131071] - fTemp76));
			float fTemp78 = 0.5f * fTemp64 * fTemp77 - fTemp63 * fRec49[1];
			float fTemp79 = fTemp64 * fTemp78 - fTemp63 * fRec52[1];
			float fTemp80 = fTemp64 * fTemp79 - fTemp63 * fRec55[1];
			fRec61[0] = fSlow18 + fConst2 * fRec61[1];
			int iTemp81 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(49.0f * fRec61[0]), 1301))];
			fRec60[0] = 0.9999f * (fRec60[1] + float(iTemp2 * iTemp81)) + 0.0001f * float(iTemp81);
			float fTemp82 = fRec60[0] + -1.49999f;
			float fTemp83 = std::floor(fTemp82);
			fVec4[IOTA0 & 16383] = fTemp63 * fRec58[1] - fTemp64 * fTemp80;
			float fTemp84 = fVec4[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp82)))) & 16383];
			fVec5[0] = fTemp84;
			fRec59[0] = fVec5[1] - (fTemp83 + (2.0f - fRec60[0])) * (fRec59[1] - fTemp84) / (fRec60[0] - fTemp83);
			fRec57[0] = fRec59[0];
			int iTemp85 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(59.0f * fRec61[0]), 1301))];
			fRec63[0] = 0.9999f * (fRec63[1] + float(iTemp2 * iTemp85)) + 0.0001f * float(iTemp85);
			float fTemp86 = fRec63[0] + -1.49999f;
			float fTemp87 = std::floor(fTemp86);
			float fTemp88 = 0.5f * fTemp60 * fTemp64 - fTemp63 * fRec48[1];
			float fTemp89 = fTemp64 * fTemp88 - fTemp63 * fRec51[1];
			float fTemp90 = fTemp64 * fTemp89 - fTemp63 * fRec54[1];
			fVec6[IOTA0 & 16383] = fTemp64 * fTemp90 - fTemp63 * fRec57[1];
			float fTemp91 = fVec6[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp86)))) & 16383];
			fVec7[0] = fTemp91;
			fRec62[0] = fVec7[1] + (fTemp87 + (2.0f - fRec63[0])) * (fTemp91 - fRec62[1]) / (fRec63[0] - fTemp87);
			fRec58[0] = fRec62[0];
			fVec8[IOTA0 & 16383] = fTemp64 * fRec58[1] + fTemp63 * fTemp80;
			int iTemp92 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(36.0f * fRec61[0]), 1301))];
			fRec64[0] = 0.9999f * (fRec64[1] + float(iTemp2 * iTemp92)) + 0.0001f * float(iTemp92);
			float fTemp93 = fRec64[0] + -1.49999f;
			float fTemp94 = fVec8[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp93)))) & 16383];
			fVec9[0] = fTemp94;
			float fTemp95 = std::floor(fTemp93);
			float fTemp96 = fRec64[0] - fTemp95;
			float fTemp97 = fTemp95 + (2.0f - fRec64[0]);
			fRec56[0] = -(fRec56[1] * fTemp97 / fTemp96 + fTemp97 * fTemp94 / fTemp96 + fVec9[1]);
			fRec54[0] = fRec56[0];
			int iTemp98 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(46.0f * fRec61[0]), 1301))];
			fRec66[0] = 0.9999f * (fRec66[1] + float(iTemp2 * iTemp98)) + 0.0001f * float(iTemp98);
			float fTemp99 = fRec66[0] + -1.49999f;
			float fTemp100 = std::floor(fTemp99);
			fVec10[IOTA0 & 16383] = fRec57[1] * fTemp64 + fTemp63 * fTemp90;
			float fTemp101 = fVec10[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp99)))) & 16383];
			fVec11[0] = fTemp101;
			fRec65[0] = fVec11[1] - (fTemp100 + (2.0f - fRec66[0])) * (fRec65[1] - fTemp101) / (fRec66[0] - fTemp100);
			fRec55[0] = fRec65[0];
			fVec12[IOTA0 & 16383] = fTemp64 * fRec55[1] + fTemp63 * fTemp79;
			int iTemp102 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(23.0f * fRec61[0]), 1301))];
			fRec67[0] = 0.9999f * (fRec67[1] + float(iTemp2 * iTemp102)) + 0.0001f * float(iTemp102);
			float fTemp103 = fRec67[0] + -1.49999f;
			float fTemp104 = fVec12[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp103)))) & 16383];
			fVec13[0] = fTemp104;
			float fTemp105 = std::floor(fTemp103);
			float fTemp106 = fRec67[0] - fTemp105;
			float fTemp107 = fTemp105 + (2.0f - fRec67[0]);
			fRec53[0] = -(fRec53[1] * fTemp107 / fTemp106 + fTemp107 * fTemp104 / fTemp106 + fVec13[1]);
			fRec51[0] = fRec53[0];
			int iTemp108 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(33.0f * fRec61[0]), 1301))];
			fRec69[0] = 0.9999f * (fRec69[1] + float(iTemp2 * iTemp108)) + 0.0001f * float(iTemp108);
			float fTemp109 = fRec69[0] + -1.49999f;
			float fTemp110 = std::floor(fTemp109);
			fVec14[IOTA0 & 16383] = fRec54[1] * fTemp64 + fTemp63 * fTemp89;
			float fTemp111 = fVec14[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp109)))) & 16383];
			fVec15[0] = fTemp111;
			fRec68[0] = fVec15[1] - (fTemp110 + (2.0f - fRec69[0])) * (fRec68[1] - fTemp111) / (fRec69[0] - fTemp110);
			fRec52[0] = fRec68[0];
			fVec16[IOTA0 & 16383] = fTemp64 * fRec52[1] + fTemp63 * fTemp78;
			int iTemp112 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(1e+01f * fRec61[0]), 1301))];
			fRec70[0] = 0.9999f * (fRec70[1] + float(iTemp2 * iTemp112)) + 0.0001f * float(iTemp112);
			float fTemp113 = fRec70[0] + -1.49999f;
			float fTemp114 = fVec16[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp113)))) & 16383];
			fVec17[0] = fTemp114;
			float fTemp115 = std::floor(fTemp113);
			float fTemp116 = fRec70[0] - fTemp115;
			float fTemp117 = fTemp115 + (2.0f - fRec70[0]);
			fRec50[0] = -(fRec50[1] * fTemp117 / fTemp116 + fTemp117 * fTemp114 / fTemp116 + fVec17[1]);
			fRec48[0] = fRec50[0];
			int iTemp118 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(2e+01f * fRec61[0]), 1301))];
			fRec72[0] = 0.9999f * (fRec72[1] + float(iTemp2 * iTemp118)) + 0.0001f * float(iTemp118);
			float fTemp119 = fRec72[0] + -1.49999f;
			float fTemp120 = std::floor(fTemp119);
			fVec18[IOTA0 & 16383] = fRec51[1] * fTemp64 + fTemp63 * fTemp88;
			float fTemp121 = fVec18[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp119)))) & 16383];
			fVec19[0] = fTemp121;
			fRec71[0] = fVec19[1] - (fTemp120 + (2.0f - fRec72[0])) * (fRec71[1] - fTemp121) / (fRec72[0] - fTemp120);
			fRec49[0] = fRec71[0];
			float fTemp122 = fRec48[1] * fTemp64 + 0.5f * fTemp63 * fTemp60;
			float fTemp123 = -0.5f * fTemp61;
			float fTemp124 = std::sin(fTemp123);
			float fTemp125 = std::cos(fTemp123);
			float fTemp126 = fTemp64 * fRec49[1] + 0.5f * fTemp63 * fTemp77;
			float fTemp127 = fTemp125 * fTemp126 - fTemp124 * fRec74[1];
			float fTemp128 = fTemp125 * fTemp127 - fTemp124 * fRec77[1];
			float fTemp129 = fTemp125 * fTemp128 - fTemp124 * fRec80[1];
			int iTemp130 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(68.0f * fRec61[0]), 1301))];
			fRec85[0] = 0.9999f * (fRec85[1] + float(iTemp2 * iTemp130)) + 0.0001f * float(iTemp130);
			float fTemp131 = fRec85[0] + -1.49999f;
			float fTemp132 = std::floor(fTemp131);
			fVec20[IOTA0 & 16383] = fTemp124 * fRec83[1] - fTemp125 * fTemp129;
			float fTemp133 = fVec20[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp131)))) & 16383];
			fVec21[0] = fTemp133;
			fRec84[0] = fVec21[1] - (fTemp132 + (2.0f - fRec85[0])) * (fRec84[1] - fTemp133) / (fRec85[0] - fTemp132);
			fRec82[0] = fRec84[0];
			int iTemp134 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(78.0f * fRec61[0]), 1301))];
			fRec87[0] = 0.9999f * (fRec87[1] + float(iTemp2 * iTemp134)) + 0.0001f * float(iTemp134);
			float fTemp135 = fRec87[0] + -1.49999f;
			float fTemp136 = std::floor(fTemp135);
			float fTemp137 = fTemp122 * fTemp125 - fTemp124 * fRec73[1];
			float fTemp138 = fTemp125 * fTemp137 - fTemp124 * fRec76[1];
			float fTemp139 = fTemp125 * fTemp138 - fTemp124 * fRec79[1];
			fVec22[IOTA0 & 16383] = fTemp125 * fTemp139 - fRec82[1] * fTemp124;
			float fTemp140 = fVec22[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp135)))) & 16383];
			fVec23[0] = fTemp140;
			fRec86[0] = fVec23[1] - (fTemp136 + (2.0f - fRec87[0])) * (fRec86[1] - fTemp140) / (fRec87[0] - fTemp136);
			fRec83[0] = fRec86[0];
			fVec24[IOTA0 & 16383] = fTemp125 * fRec83[1] + fTemp124 * fTemp129;
			int iTemp141 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(55.0f * fRec61[0]), 1301))];
			fRec88[0] = 0.9999f * (fRec88[1] + float(iTemp2 * iTemp141)) + 0.0001f * float(iTemp141);
			float fTemp142 = fRec88[0] + -1.49999f;
			float fTemp143 = fVec24[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp142)))) & 16383];
			fVec25[0] = fTemp143;
			float fTemp144 = std::floor(fTemp142);
			float fTemp145 = fRec88[0] - fTemp144;
			float fTemp146 = fTemp144 + (2.0f - fRec88[0]);
			fRec81[0] = -(fRec81[1] * fTemp146 / fTemp145 + fTemp146 * fTemp143 / fTemp145 + fVec25[1]);
			fRec79[0] = fRec81[0];
			int iTemp147 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(65.0f * fRec61[0]), 1301))];
			fRec90[0] = 0.9999f * (fRec90[1] + float(iTemp2 * iTemp147)) + 0.0001f * float(iTemp147);
			float fTemp148 = fRec90[0] + -1.49999f;
			float fTemp149 = std::floor(fTemp148);
			fVec26[IOTA0 & 16383] = fRec82[1] * fTemp125 + fTemp124 * fTemp139;
			float fTemp150 = fVec26[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp148)))) & 16383];
			fVec27[0] = fTemp150;
			fRec89[0] = fVec27[1] - (fTemp149 + (2.0f - fRec90[0])) * (fRec89[1] - fTemp150) / (fRec90[0] - fTemp149);
			fRec80[0] = fRec89[0];
			fVec28[IOTA0 & 16383] = fTemp125 * fRec80[1] + fTemp124 * fTemp128;
			int iTemp151 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(42.0f * fRec61[0]), 1301))];
			fRec91[0] = 0.9999f * (fRec91[1] + float(iTemp2 * iTemp151)) + 0.0001f * float(iTemp151);
			float fTemp152 = fRec91[0] + -1.49999f;
			float fTemp153 = fVec28[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp152)))) & 16383];
			fVec29[0] = fTemp153;
			float fTemp154 = std::floor(fTemp152);
			float fTemp155 = fRec91[0] - fTemp154;
			float fTemp156 = fTemp154 + (2.0f - fRec91[0]);
			fRec78[0] = -(fRec78[1] * fTemp156 / fTemp155 + fTemp156 * fTemp153 / fTemp155 + fVec29[1]);
			fRec76[0] = fRec78[0];
			int iTemp157 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(52.0f * fRec61[0]), 1301))];
			fRec93[0] = 0.9999f * (fRec93[1] + float(iTemp2 * iTemp157)) + 0.0001f * float(iTemp157);
			float fTemp158 = fRec93[0] + -1.49999f;
			float fTemp159 = std::floor(fTemp158);
			fVec30[IOTA0 & 16383] = fRec79[1] * fTemp125 + fTemp124 * fTemp138;
			float fTemp160 = fVec30[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp158)))) & 16383];
			fVec31[0] = fTemp160;
			fRec92[0] = fVec31[1] - (fTemp159 + (2.0f - fRec93[0])) * (fRec92[1] - fTemp160) / (fRec93[0] - fTemp159);
			fRec77[0] = fRec92[0];
			fVec32[IOTA0 & 16383] = fTemp125 * fRec77[1] + fTemp124 * fTemp127;
			int iTemp161 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(29.0f * fRec61[0]), 1301))];
			fRec94[0] = 0.9999f * (fRec94[1] + float(iTemp2 * iTemp161)) + 0.0001f * float(iTemp161);
			float fTemp162 = fRec94[0] + -1.49999f;
			float fTemp163 = fVec32[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp162)))) & 16383];
			fVec33[0] = fTemp163;
			float fTemp164 = std::floor(fTemp162);
			float fTemp165 = fRec94[0] - fTemp164;
			float fTemp166 = fTemp164 + (2.0f - fRec94[0]);
			fRec75[0] = -(fRec75[1] * fTemp166 / fTemp165 + fTemp166 * fTemp163 / fTemp165 + fVec33[1]);
			fRec73[0] = fRec75[0];
			int iTemp167 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(39.0f * fRec61[0]), 1301))];
			fRec96[0] = 0.9999f * (fRec96[1] + float(iTemp2 * iTemp167)) + 0.0001f * float(iTemp167);
			float fTemp168 = fRec96[0] + -1.49999f;
			float fTemp169 = std::floor(fTemp168);
			fVec34[IOTA0 & 16383] = fRec76[1] * fTemp125 + fTemp124 * fTemp137;
			float fTemp170 = fVec34[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp168)))) & 16383];
			fVec35[0] = fTemp170;
			fRec95[0] = fVec35[1] - (fTemp169 + (2.0f - fRec96[0])) * (fRec95[1] - fTemp170) / (fRec96[0] - fTemp169);
			fRec74[0] = fRec95[0];
			float fTemp171 = fRec73[1] * fTemp125 + fTemp124 * fTemp122;
			float fTemp172 = fTemp125 * fRec74[1] + fTemp124 * fTemp126;
			float fTemp173 = fTemp64 * fTemp172 - fTemp63 * fRec98[1];
			float fTemp174 = fTemp64 * fTemp173 - fTemp63 * fRec101[1];
			float fTemp175 = fTemp64 * fTemp174 - fTemp63 * fRec104[1];
			int iTemp176 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(87.0f * fRec61[0]), 1301))];
			fRec109[0] = 0.9999f * (fRec109[1] + float(iTemp2 * iTemp176)) + 0.0001f * float(iTemp176);
			float fTemp177 = fRec109[0] + -1.49999f;
			float fTemp178 = std::floor(fTemp177);
			fVec36[IOTA0 & 16383] = fTemp63 * fRec107[1] - fTemp64 * fTemp175;
			float fTemp179 = fVec36[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp177)))) & 16383];
			fVec37[0] = fTemp179;
			fRec108[0] = fVec37[1] - (fTemp178 + (2.0f - fRec109[0])) * (fRec108[1] - fTemp179) / (fRec109[0] - fTemp178);
			fRec106[0] = fRec108[0];
			int iTemp180 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(97.0f * fRec61[0]), 1301))];
			fRec111[0] = 0.9999f * (fRec111[1] + float(iTemp2 * iTemp180)) + 0.0001f * float(iTemp180);
			float fTemp181 = fRec111[0] + -1.49999f;
			float fTemp182 = std::floor(fTemp181);
			float fTemp183 = fTemp64 * fTemp171 - fTemp63 * fRec97[1];
			float fTemp184 = fTemp64 * fTemp183 - fTemp63 * fRec100[1];
			float fTemp185 = fTemp64 * fTemp184 - fTemp63 * fRec103[1];
			fVec38[IOTA0 & 16383] = fTemp64 * fTemp185 - fRec106[1] * fTemp63;
			float fTemp186 = fVec38[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp181)))) & 16383];
			fVec39[0] = fTemp186;
			fRec110[0] = fVec39[1] - (fTemp182 + (2.0f - fRec111[0])) * (fRec110[1] - fTemp186) / (fRec111[0] - fTemp182);
			fRec107[0] = fRec110[0];
			fVec40[IOTA0 & 16383] = fTemp64 * fRec107[1] + fTemp63 * fTemp175;
			int iTemp187 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(74.0f * fRec61[0]), 1301))];
			fRec112[0] = 0.9999f * (fRec112[1] + float(iTemp2 * iTemp187)) + 0.0001f * float(iTemp187);
			float fTemp188 = fRec112[0] + -1.49999f;
			float fTemp189 = fVec40[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp188)))) & 16383];
			fVec41[0] = fTemp189;
			float fTemp190 = std::floor(fTemp188);
			float fTemp191 = fRec112[0] - fTemp190;
			float fTemp192 = fTemp190 + (2.0f - fRec112[0]);
			fRec105[0] = -(fRec105[1] * fTemp192 / fTemp191 + fTemp192 * fTemp189 / fTemp191 + fVec41[1]);
			fRec103[0] = fRec105[0];
			int iTemp193 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(84.0f * fRec61[0]), 1301))];
			fRec114[0] = 0.9999f * (fRec114[1] + float(iTemp2 * iTemp193)) + 0.0001f * float(iTemp193);
			float fTemp194 = fRec114[0] + -1.49999f;
			float fTemp195 = std::floor(fTemp194);
			fVec42[IOTA0 & 16383] = fRec106[1] * fTemp64 + fTemp63 * fTemp185;
			float fTemp196 = fVec42[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp194)))) & 16383];
			fVec43[0] = fTemp196;
			fRec113[0] = fVec43[1] - (fTemp195 + (2.0f - fRec114[0])) * (fRec113[1] - fTemp196) / (fRec114[0] - fTemp195);
			fRec104[0] = fRec113[0];
			fVec44[IOTA0 & 16383] = fTemp64 * fRec104[1] + fTemp63 * fTemp174;
			int iTemp197 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(61.0f * fRec61[0]), 1301))];
			fRec115[0] = 0.9999f * (fRec115[1] + float(iTemp2 * iTemp197)) + 0.0001f * float(iTemp197);
			float fTemp198 = fRec115[0] + -1.49999f;
			float fTemp199 = fVec44[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp198)))) & 16383];
			fVec45[0] = fTemp199;
			float fTemp200 = std::floor(fTemp198);
			float fTemp201 = fRec115[0] - fTemp200;
			float fTemp202 = fTemp200 + (2.0f - fRec115[0]);
			fRec102[0] = -(fRec102[1] * fTemp202 / fTemp201 + fTemp202 * fTemp199 / fTemp201 + fVec45[1]);
			fRec100[0] = fRec102[0];
			int iTemp203 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(71.0f * fRec61[0]), 1301))];
			fRec117[0] = 0.9999f * (fRec117[1] + float(iTemp2 * iTemp203)) + 0.0001f * float(iTemp203);
			float fTemp204 = fRec117[0] + -1.49999f;
			float fTemp205 = std::floor(fTemp204);
			fVec46[IOTA0 & 16383] = fRec103[1] * fTemp64 + fTemp63 * fTemp184;
			float fTemp206 = fVec46[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp204)))) & 16383];
			fVec47[0] = fTemp206;
			fRec116[0] = fVec47[1] - (fTemp205 + (2.0f - fRec117[0])) * (fRec116[1] - fTemp206) / (fRec117[0] - fTemp205);
			fRec101[0] = fRec116[0];
			fVec48[IOTA0 & 16383] = fTemp64 * fRec101[1] + fTemp63 * fTemp173;
			int iTemp207 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(48.0f * fRec61[0]), 1301))];
			fRec118[0] = 0.9999f * (fRec118[1] + float(iTemp2 * iTemp207)) + 0.0001f * float(iTemp207);
			float fTemp208 = fRec118[0] + -1.49999f;
			float fTemp209 = fVec48[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp208)))) & 16383];
			fVec49[0] = fTemp209;
			float fTemp210 = std::floor(fTemp208);
			float fTemp211 = fRec118[0] - fTemp210;
			float fTemp212 = fTemp210 + (2.0f - fRec118[0]);
			fRec99[0] = -(fRec99[1] * fTemp212 / fTemp211 + fTemp212 * fTemp209 / fTemp211 + fVec49[1]);
			fRec97[0] = fRec99[0];
			int iTemp213 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(58.0f * fRec61[0]), 1301))];
			fRec120[0] = 0.9999f * (fRec120[1] + float(iTemp2 * iTemp213)) + 0.0001f * float(iTemp213);
			float fTemp214 = fRec120[0] + -1.49999f;
			float fTemp215 = std::floor(fTemp214);
			fVec50[IOTA0 & 16383] = fRec100[1] * fTemp64 + fTemp63 * fTemp183;
			float fTemp216 = fVec50[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp214)))) & 16383];
			fVec51[0] = fTemp216;
			fRec119[0] = fVec51[1] - (fTemp215 + (2.0f - fRec120[0])) * (fRec119[1] - fTemp216) / (fRec120[0] - fTemp215);
			fRec98[0] = fRec119[0];
			float fTemp217 = 1.0f - 0.5f * fTemp37;
			fRec35[0] = fTemp217 * (fRec97[1] * fTemp64 + fTemp63 * fTemp171) + 0.5f * fTemp37 * fRec35[1];
			fRec33[IOTA0 & 1023] = fRec35[0];
			fRec121[0] = fTemp217 * (fTemp64 * fRec98[1] + fTemp63 * fTemp172) + 0.5f * fTemp37 * fRec121[1];
			fRec34[IOTA0 & 1023] = fRec121[0];
			output0[i0] = FAUSTFLOAT(fRec33[IOTA0 & 1023] * fRec31[0] + fTemp36);
			output1[i0] = FAUSTFLOAT(fTemp36 + fRec31[0] * fRec34[IOTA0 & 1023]);
			iVec0[1] = iVec0[0];
			fRec1[1] = fRec1[0];
			fRec6[1] = fRec6[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fRec10[1] = fRec10[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec15[1] = fRec15[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			fRec25[1] = fRec25[0];
			fRec30[1] = fRec30[0];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fRec24[1] = fRec24[0];
			fRec31[1] = fRec31[0];
			fRec32[1] = fRec32[0];
			fRec36[1] = fRec36[0];
			fRec37[1] = fRec37[0];
			IOTA0 = IOTA0 + 1;
			fRec40[1] = fRec40[0];
			fRec38[1] = fRec38[0];
			fRec39[1] = fRec39[0];
			fRec41[1] = fRec41[0];
			fRec46[1] = fRec46[0];
			fRec42[1] = fRec42[0];
			fRec43[1] = fRec43[0];
			fRec44[1] = fRec44[0];
			fRec45[1] = fRec45[0];
			fRec47[1] = fRec47[0];
			fRec61[1] = fRec61[0];
			fRec60[1] = fRec60[0];
			fVec5[1] = fVec5[0];
			fRec59[1] = fRec59[0];
			fRec57[1] = fRec57[0];
			fRec63[1] = fRec63[0];
			fVec7[1] = fVec7[0];
			fRec62[1] = fRec62[0];
			fRec58[1] = fRec58[0];
			fRec64[1] = fRec64[0];
			fVec9[1] = fVec9[0];
			fRec56[1] = fRec56[0];
			fRec54[1] = fRec54[0];
			fRec66[1] = fRec66[0];
			fVec11[1] = fVec11[0];
			fRec65[1] = fRec65[0];
			fRec55[1] = fRec55[0];
			fRec67[1] = fRec67[0];
			fVec13[1] = fVec13[0];
			fRec53[1] = fRec53[0];
			fRec51[1] = fRec51[0];
			fRec69[1] = fRec69[0];
			fVec15[1] = fVec15[0];
			fRec68[1] = fRec68[0];
			fRec52[1] = fRec52[0];
			fRec70[1] = fRec70[0];
			fVec17[1] = fVec17[0];
			fRec50[1] = fRec50[0];
			fRec48[1] = fRec48[0];
			fRec72[1] = fRec72[0];
			fVec19[1] = fVec19[0];
			fRec71[1] = fRec71[0];
			fRec49[1] = fRec49[0];
			fRec85[1] = fRec85[0];
			fVec21[1] = fVec21[0];
			fRec84[1] = fRec84[0];
			fRec82[1] = fRec82[0];
			fRec87[1] = fRec87[0];
			fVec23[1] = fVec23[0];
			fRec86[1] = fRec86[0];
			fRec83[1] = fRec83[0];
			fRec88[1] = fRec88[0];
			fVec25[1] = fVec25[0];
			fRec81[1] = fRec81[0];
			fRec79[1] = fRec79[0];
			fRec90[1] = fRec90[0];
			fVec27[1] = fVec27[0];
			fRec89[1] = fRec89[0];
			fRec80[1] = fRec80[0];
			fRec91[1] = fRec91[0];
			fVec29[1] = fVec29[0];
			fRec78[1] = fRec78[0];
			fRec76[1] = fRec76[0];
			fRec93[1] = fRec93[0];
			fVec31[1] = fVec31[0];
			fRec92[1] = fRec92[0];
			fRec77[1] = fRec77[0];
			fRec94[1] = fRec94[0];
			fVec33[1] = fVec33[0];
			fRec75[1] = fRec75[0];
			fRec73[1] = fRec73[0];
			fRec96[1] = fRec96[0];
			fVec35[1] = fVec35[0];
			fRec95[1] = fRec95[0];
			fRec74[1] = fRec74[0];
			fRec109[1] = fRec109[0];
			fVec37[1] = fVec37[0];
			fRec108[1] = fRec108[0];
			fRec106[1] = fRec106[0];
			fRec111[1] = fRec111[0];
			fVec39[1] = fVec39[0];
			fRec110[1] = fRec110[0];
			fRec107[1] = fRec107[0];
			fRec112[1] = fRec112[0];
			fVec41[1] = fVec41[0];
			fRec105[1] = fRec105[0];
			fRec103[1] = fRec103[0];
			fRec114[1] = fRec114[0];
			fVec43[1] = fVec43[0];
			fRec113[1] = fRec113[0];
			fRec104[1] = fRec104[0];
			fRec115[1] = fRec115[0];
			fVec45[1] = fVec45[0];
			fRec102[1] = fRec102[0];
			fRec100[1] = fRec100[0];
			fRec117[1] = fRec117[0];
			fVec47[1] = fVec47[0];
			fRec116[1] = fRec116[0];
			fRec101[1] = fRec101[0];
			fRec118[1] = fRec118[0];
			fVec49[1] = fVec49[0];
			fRec99[1] = fRec99[0];
			fRec97[1] = fRec97[0];
			fRec120[1] = fRec120[0];
			fVec51[1] = fVec51[0];
			fRec119[1] = fRec119[0];
			fRec98[1] = fRec98[0];
			fRec35[1] = fRec35[0];
			fRec121[1] = fRec121[0];
		}
	}

};

// END-FAUSTDSP

#endif
