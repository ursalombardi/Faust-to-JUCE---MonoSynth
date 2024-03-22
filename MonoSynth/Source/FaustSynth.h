/* ------------------------------------------------------------
name: "UrsynthForExport"
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
	
	int iVec2[2];
	int iRec40[2];
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			iVec2[l34] = 0;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			iRec40[l35] = 0;
		}
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec2[0] = 1;
			iRec40[0] = (iVec2[1] + iRec40[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * float(iRec40[0]));
			iVec2[1] = iVec2[0];
			iRec40[1] = iRec40[0];
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
	
	FAUSTFLOAT fCheckbox0;
	int iVec0[2];
	FAUSTFLOAT fCheckbox1;
	int iVec1[2];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	float fConst0;
	int iRec1[2];
	FAUSTFLOAT fHslider2;
	float fConst1;
	float fRec0[2];
	float fConst2;
	float fConst3;
	FAUSTFLOAT fVslider0;
	float fRec3[2];
	float fConst4;
	FAUSTFLOAT fVslider1;
	float fRec8[2];
	FAUSTFLOAT fHslider3;
	float fRec11[2];
	float fRec9[2];
	FAUSTFLOAT fHslider4;
	float fRec12[2];
	float fRec7[2];
	float fRec6[2];
	float fRec5[2];
	float fRec4[2];
	float fRec2[2];
	FAUSTFLOAT fVslider2;
	float fRec14[2];
	FAUSTFLOAT fVslider3;
	float fRec19[2];
	FAUSTFLOAT fHslider5;
	float fRec20[2];
	float fRec21[2];
	float fRec18[2];
	float fRec17[2];
	float fRec16[2];
	float fRec15[2];
	float fRec13[2];
	FAUSTFLOAT fVslider4;
	float fRec24[2];
	FAUSTFLOAT fVslider5;
	float fRec29[2];
	float fRec30[2];
	FAUSTFLOAT fHslider6;
	float fRec32[2];
	float fRec28[2];
	float fRec27[2];
	float fRec26[2];
	float fRec25[2];
	float fRec23[2];
	FAUSTFLOAT fVslider6;
	float fRec34[2];
	FAUSTFLOAT fVslider7;
	float fRec39[2];
	float fRec41[2];
	float fRec38[2];
	float fRec37[2];
	float fRec36[2];
	float fRec35[2];
	float fRec33[2];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHslider8;
	float fRec42[2];
	FAUSTFLOAT fHslider9;
	float fRec43[2];
	FAUSTFLOAT fHslider10;
	float fRec47[2];
	FAUSTFLOAT fHslider11;
	float fRec48[2];
	int IOTA0;
	FAUSTFLOAT fHslider12;
	float fRec51[2];
	float fConst5;
	float fRec49[2];
	float fRec50[2];
	FAUSTFLOAT fHslider13;
	float fRec52[2];
	float fConst6;
	float fVec3[131072];
	FAUSTFLOAT fHslider14;
	float fRec57[2];
	float fRec53[2];
	float fRec54[2];
	float fRec55[2];
	float fRec56[2];
	FAUSTFLOAT fHslider15;
	float fRec58[2];
	float fVec4[131072];
	FAUSTFLOAT fHslider16;
	float fRec72[2];
	float fRec71[2];
	float fVec5[16384];
	float fVec6[2];
	float fRec70[2];
	float fRec68[2];
	float fRec74[2];
	float fVec7[16384];
	float fVec8[2];
	float fRec73[2];
	float fRec69[2];
	float fVec9[16384];
	float fRec75[2];
	float fVec10[2];
	float fRec67[2];
	float fRec65[2];
	float fRec77[2];
	float fVec11[16384];
	float fVec12[2];
	float fRec76[2];
	float fRec66[2];
	float fVec13[16384];
	float fRec78[2];
	float fVec14[2];
	float fRec64[2];
	float fRec62[2];
	float fRec80[2];
	float fVec15[16384];
	float fVec16[2];
	float fRec79[2];
	float fRec63[2];
	float fVec17[16384];
	float fRec81[2];
	float fVec18[2];
	float fRec61[2];
	float fRec59[2];
	float fRec83[2];
	float fVec19[16384];
	float fVec20[2];
	float fRec82[2];
	float fRec60[2];
	float fRec96[2];
	float fVec21[16384];
	float fVec22[2];
	float fRec95[2];
	float fRec93[2];
	float fRec98[2];
	float fVec23[16384];
	float fVec24[2];
	float fRec97[2];
	float fRec94[2];
	float fVec25[16384];
	float fRec99[2];
	float fVec26[2];
	float fRec92[2];
	float fRec90[2];
	float fRec101[2];
	float fVec27[16384];
	float fVec28[2];
	float fRec100[2];
	float fRec91[2];
	float fVec29[16384];
	float fRec102[2];
	float fVec30[2];
	float fRec89[2];
	float fRec87[2];
	float fRec104[2];
	float fVec31[16384];
	float fVec32[2];
	float fRec103[2];
	float fRec88[2];
	float fVec33[16384];
	float fRec105[2];
	float fVec34[2];
	float fRec86[2];
	float fRec84[2];
	float fRec107[2];
	float fVec35[16384];
	float fVec36[2];
	float fRec106[2];
	float fRec85[2];
	float fRec120[2];
	float fVec37[16384];
	float fVec38[2];
	float fRec119[2];
	float fRec117[2];
	float fRec122[2];
	float fVec39[16384];
	float fVec40[2];
	float fRec121[2];
	float fRec118[2];
	float fVec41[16384];
	float fRec123[2];
	float fVec42[2];
	float fRec116[2];
	float fRec114[2];
	float fRec125[2];
	float fVec43[16384];
	float fVec44[2];
	float fRec124[2];
	float fRec115[2];
	float fVec45[16384];
	float fRec126[2];
	float fVec46[2];
	float fRec113[2];
	float fRec111[2];
	float fRec128[2];
	float fVec47[16384];
	float fVec48[2];
	float fRec127[2];
	float fRec112[2];
	float fVec49[16384];
	float fRec129[2];
	float fVec50[2];
	float fRec110[2];
	float fRec108[2];
	float fRec131[2];
	float fVec51[16384];
	float fVec52[2];
	float fRec130[2];
	float fRec109[2];
	float fRec46[2];
	float fRec44[1024];
	float fRec132[2];
	float fRec45[1024];
	
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
		m->declare("envelopes.lib/adsre:author", "Julius O. Smith III");
		m->declare("envelopes.lib/adsre:licence", "STK-4.3");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "1.3.0");
		m->declare("filename", "UrsynthForExport.dsp");
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
		m->declare("name", "UrsynthForExport");
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
		fConst1 = 1.0f / fConst0;
		fConst2 = 44.1f / fConst0;
		fConst3 = 1.0f - fConst2;
		fConst4 = 6.2831855f / fConst0;
		fConst5 = 3.1415927f / fConst0;
		fConst6 = 0.00056689343f * fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.1f);
		fHslider2 = FAUSTFLOAT(1.0f);
		fVslider0 = FAUSTFLOAT(2e+03f);
		fVslider1 = FAUSTFLOAT(0.5f);
		fHslider3 = FAUSTFLOAT(2e+02f);
		fHslider4 = FAUSTFLOAT(0.2f);
		fVslider2 = FAUSTFLOAT(2e+03f);
		fVslider3 = FAUSTFLOAT(0.5f);
		fHslider5 = FAUSTFLOAT(0.95f);
		fVslider4 = FAUSTFLOAT(2e+03f);
		fVslider5 = FAUSTFLOAT(0.5f);
		fHslider6 = FAUSTFLOAT(0.65f);
		fVslider6 = FAUSTFLOAT(2e+02f);
		fVslider7 = FAUSTFLOAT(0.7f);
		fHslider7 = FAUSTFLOAT(1.0f);
		fHslider8 = FAUSTFLOAT(1.0f);
		fHslider9 = FAUSTFLOAT(0.5f);
		fHslider10 = FAUSTFLOAT(0.0f);
		fHslider11 = FAUSTFLOAT(0.5f);
		fHslider12 = FAUSTFLOAT(1.0f);
		fHslider13 = FAUSTFLOAT(0.0f);
		fHslider14 = FAUSTFLOAT(0.1f);
		fHslider15 = FAUSTFLOAT(0.5f);
		fHslider16 = FAUSTFLOAT(1.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iVec1[l1] = 0;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			iRec1[l2] = 0;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec0[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec3[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec8[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec11[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec9[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec12[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec7[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec6[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec5[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec4[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec2[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec14[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec19[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec20[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec21[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec18[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec17[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec16[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fRec15[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fRec13[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec24[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fRec29[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec30[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			fRec32[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec28[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			fRec27[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec26[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			fRec25[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec23[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 2; l32 = l32 + 1) {
			fRec34[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fRec39[l33] = 0.0f;
		}
		for (int l36 = 0; l36 < 2; l36 = l36 + 1) {
			fRec41[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec38[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 2; l38 = l38 + 1) {
			fRec37[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			fRec36[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			fRec35[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			fRec33[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 2; l42 = l42 + 1) {
			fRec42[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec43[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 2; l44 = l44 + 1) {
			fRec47[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 2; l45 = l45 + 1) {
			fRec48[l45] = 0.0f;
		}
		IOTA0 = 0;
		for (int l46 = 0; l46 < 2; l46 = l46 + 1) {
			fRec51[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 2; l47 = l47 + 1) {
			fRec49[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 2; l48 = l48 + 1) {
			fRec50[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 2; l49 = l49 + 1) {
			fRec52[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 131072; l50 = l50 + 1) {
			fVec3[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 2; l51 = l51 + 1) {
			fRec57[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 2; l52 = l52 + 1) {
			fRec53[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 2; l53 = l53 + 1) {
			fRec54[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 2; l54 = l54 + 1) {
			fRec55[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 2; l55 = l55 + 1) {
			fRec56[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 2; l56 = l56 + 1) {
			fRec58[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 131072; l57 = l57 + 1) {
			fVec4[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 2; l58 = l58 + 1) {
			fRec72[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 2; l59 = l59 + 1) {
			fRec71[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 16384; l60 = l60 + 1) {
			fVec5[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 2; l61 = l61 + 1) {
			fVec6[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 2; l62 = l62 + 1) {
			fRec70[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 2; l63 = l63 + 1) {
			fRec68[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 2; l64 = l64 + 1) {
			fRec74[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 16384; l65 = l65 + 1) {
			fVec7[l65] = 0.0f;
		}
		for (int l66 = 0; l66 < 2; l66 = l66 + 1) {
			fVec8[l66] = 0.0f;
		}
		for (int l67 = 0; l67 < 2; l67 = l67 + 1) {
			fRec73[l67] = 0.0f;
		}
		for (int l68 = 0; l68 < 2; l68 = l68 + 1) {
			fRec69[l68] = 0.0f;
		}
		for (int l69 = 0; l69 < 16384; l69 = l69 + 1) {
			fVec9[l69] = 0.0f;
		}
		for (int l70 = 0; l70 < 2; l70 = l70 + 1) {
			fRec75[l70] = 0.0f;
		}
		for (int l71 = 0; l71 < 2; l71 = l71 + 1) {
			fVec10[l71] = 0.0f;
		}
		for (int l72 = 0; l72 < 2; l72 = l72 + 1) {
			fRec67[l72] = 0.0f;
		}
		for (int l73 = 0; l73 < 2; l73 = l73 + 1) {
			fRec65[l73] = 0.0f;
		}
		for (int l74 = 0; l74 < 2; l74 = l74 + 1) {
			fRec77[l74] = 0.0f;
		}
		for (int l75 = 0; l75 < 16384; l75 = l75 + 1) {
			fVec11[l75] = 0.0f;
		}
		for (int l76 = 0; l76 < 2; l76 = l76 + 1) {
			fVec12[l76] = 0.0f;
		}
		for (int l77 = 0; l77 < 2; l77 = l77 + 1) {
			fRec76[l77] = 0.0f;
		}
		for (int l78 = 0; l78 < 2; l78 = l78 + 1) {
			fRec66[l78] = 0.0f;
		}
		for (int l79 = 0; l79 < 16384; l79 = l79 + 1) {
			fVec13[l79] = 0.0f;
		}
		for (int l80 = 0; l80 < 2; l80 = l80 + 1) {
			fRec78[l80] = 0.0f;
		}
		for (int l81 = 0; l81 < 2; l81 = l81 + 1) {
			fVec14[l81] = 0.0f;
		}
		for (int l82 = 0; l82 < 2; l82 = l82 + 1) {
			fRec64[l82] = 0.0f;
		}
		for (int l83 = 0; l83 < 2; l83 = l83 + 1) {
			fRec62[l83] = 0.0f;
		}
		for (int l84 = 0; l84 < 2; l84 = l84 + 1) {
			fRec80[l84] = 0.0f;
		}
		for (int l85 = 0; l85 < 16384; l85 = l85 + 1) {
			fVec15[l85] = 0.0f;
		}
		for (int l86 = 0; l86 < 2; l86 = l86 + 1) {
			fVec16[l86] = 0.0f;
		}
		for (int l87 = 0; l87 < 2; l87 = l87 + 1) {
			fRec79[l87] = 0.0f;
		}
		for (int l88 = 0; l88 < 2; l88 = l88 + 1) {
			fRec63[l88] = 0.0f;
		}
		for (int l89 = 0; l89 < 16384; l89 = l89 + 1) {
			fVec17[l89] = 0.0f;
		}
		for (int l90 = 0; l90 < 2; l90 = l90 + 1) {
			fRec81[l90] = 0.0f;
		}
		for (int l91 = 0; l91 < 2; l91 = l91 + 1) {
			fVec18[l91] = 0.0f;
		}
		for (int l92 = 0; l92 < 2; l92 = l92 + 1) {
			fRec61[l92] = 0.0f;
		}
		for (int l93 = 0; l93 < 2; l93 = l93 + 1) {
			fRec59[l93] = 0.0f;
		}
		for (int l94 = 0; l94 < 2; l94 = l94 + 1) {
			fRec83[l94] = 0.0f;
		}
		for (int l95 = 0; l95 < 16384; l95 = l95 + 1) {
			fVec19[l95] = 0.0f;
		}
		for (int l96 = 0; l96 < 2; l96 = l96 + 1) {
			fVec20[l96] = 0.0f;
		}
		for (int l97 = 0; l97 < 2; l97 = l97 + 1) {
			fRec82[l97] = 0.0f;
		}
		for (int l98 = 0; l98 < 2; l98 = l98 + 1) {
			fRec60[l98] = 0.0f;
		}
		for (int l99 = 0; l99 < 2; l99 = l99 + 1) {
			fRec96[l99] = 0.0f;
		}
		for (int l100 = 0; l100 < 16384; l100 = l100 + 1) {
			fVec21[l100] = 0.0f;
		}
		for (int l101 = 0; l101 < 2; l101 = l101 + 1) {
			fVec22[l101] = 0.0f;
		}
		for (int l102 = 0; l102 < 2; l102 = l102 + 1) {
			fRec95[l102] = 0.0f;
		}
		for (int l103 = 0; l103 < 2; l103 = l103 + 1) {
			fRec93[l103] = 0.0f;
		}
		for (int l104 = 0; l104 < 2; l104 = l104 + 1) {
			fRec98[l104] = 0.0f;
		}
		for (int l105 = 0; l105 < 16384; l105 = l105 + 1) {
			fVec23[l105] = 0.0f;
		}
		for (int l106 = 0; l106 < 2; l106 = l106 + 1) {
			fVec24[l106] = 0.0f;
		}
		for (int l107 = 0; l107 < 2; l107 = l107 + 1) {
			fRec97[l107] = 0.0f;
		}
		for (int l108 = 0; l108 < 2; l108 = l108 + 1) {
			fRec94[l108] = 0.0f;
		}
		for (int l109 = 0; l109 < 16384; l109 = l109 + 1) {
			fVec25[l109] = 0.0f;
		}
		for (int l110 = 0; l110 < 2; l110 = l110 + 1) {
			fRec99[l110] = 0.0f;
		}
		for (int l111 = 0; l111 < 2; l111 = l111 + 1) {
			fVec26[l111] = 0.0f;
		}
		for (int l112 = 0; l112 < 2; l112 = l112 + 1) {
			fRec92[l112] = 0.0f;
		}
		for (int l113 = 0; l113 < 2; l113 = l113 + 1) {
			fRec90[l113] = 0.0f;
		}
		for (int l114 = 0; l114 < 2; l114 = l114 + 1) {
			fRec101[l114] = 0.0f;
		}
		for (int l115 = 0; l115 < 16384; l115 = l115 + 1) {
			fVec27[l115] = 0.0f;
		}
		for (int l116 = 0; l116 < 2; l116 = l116 + 1) {
			fVec28[l116] = 0.0f;
		}
		for (int l117 = 0; l117 < 2; l117 = l117 + 1) {
			fRec100[l117] = 0.0f;
		}
		for (int l118 = 0; l118 < 2; l118 = l118 + 1) {
			fRec91[l118] = 0.0f;
		}
		for (int l119 = 0; l119 < 16384; l119 = l119 + 1) {
			fVec29[l119] = 0.0f;
		}
		for (int l120 = 0; l120 < 2; l120 = l120 + 1) {
			fRec102[l120] = 0.0f;
		}
		for (int l121 = 0; l121 < 2; l121 = l121 + 1) {
			fVec30[l121] = 0.0f;
		}
		for (int l122 = 0; l122 < 2; l122 = l122 + 1) {
			fRec89[l122] = 0.0f;
		}
		for (int l123 = 0; l123 < 2; l123 = l123 + 1) {
			fRec87[l123] = 0.0f;
		}
		for (int l124 = 0; l124 < 2; l124 = l124 + 1) {
			fRec104[l124] = 0.0f;
		}
		for (int l125 = 0; l125 < 16384; l125 = l125 + 1) {
			fVec31[l125] = 0.0f;
		}
		for (int l126 = 0; l126 < 2; l126 = l126 + 1) {
			fVec32[l126] = 0.0f;
		}
		for (int l127 = 0; l127 < 2; l127 = l127 + 1) {
			fRec103[l127] = 0.0f;
		}
		for (int l128 = 0; l128 < 2; l128 = l128 + 1) {
			fRec88[l128] = 0.0f;
		}
		for (int l129 = 0; l129 < 16384; l129 = l129 + 1) {
			fVec33[l129] = 0.0f;
		}
		for (int l130 = 0; l130 < 2; l130 = l130 + 1) {
			fRec105[l130] = 0.0f;
		}
		for (int l131 = 0; l131 < 2; l131 = l131 + 1) {
			fVec34[l131] = 0.0f;
		}
		for (int l132 = 0; l132 < 2; l132 = l132 + 1) {
			fRec86[l132] = 0.0f;
		}
		for (int l133 = 0; l133 < 2; l133 = l133 + 1) {
			fRec84[l133] = 0.0f;
		}
		for (int l134 = 0; l134 < 2; l134 = l134 + 1) {
			fRec107[l134] = 0.0f;
		}
		for (int l135 = 0; l135 < 16384; l135 = l135 + 1) {
			fVec35[l135] = 0.0f;
		}
		for (int l136 = 0; l136 < 2; l136 = l136 + 1) {
			fVec36[l136] = 0.0f;
		}
		for (int l137 = 0; l137 < 2; l137 = l137 + 1) {
			fRec106[l137] = 0.0f;
		}
		for (int l138 = 0; l138 < 2; l138 = l138 + 1) {
			fRec85[l138] = 0.0f;
		}
		for (int l139 = 0; l139 < 2; l139 = l139 + 1) {
			fRec120[l139] = 0.0f;
		}
		for (int l140 = 0; l140 < 16384; l140 = l140 + 1) {
			fVec37[l140] = 0.0f;
		}
		for (int l141 = 0; l141 < 2; l141 = l141 + 1) {
			fVec38[l141] = 0.0f;
		}
		for (int l142 = 0; l142 < 2; l142 = l142 + 1) {
			fRec119[l142] = 0.0f;
		}
		for (int l143 = 0; l143 < 2; l143 = l143 + 1) {
			fRec117[l143] = 0.0f;
		}
		for (int l144 = 0; l144 < 2; l144 = l144 + 1) {
			fRec122[l144] = 0.0f;
		}
		for (int l145 = 0; l145 < 16384; l145 = l145 + 1) {
			fVec39[l145] = 0.0f;
		}
		for (int l146 = 0; l146 < 2; l146 = l146 + 1) {
			fVec40[l146] = 0.0f;
		}
		for (int l147 = 0; l147 < 2; l147 = l147 + 1) {
			fRec121[l147] = 0.0f;
		}
		for (int l148 = 0; l148 < 2; l148 = l148 + 1) {
			fRec118[l148] = 0.0f;
		}
		for (int l149 = 0; l149 < 16384; l149 = l149 + 1) {
			fVec41[l149] = 0.0f;
		}
		for (int l150 = 0; l150 < 2; l150 = l150 + 1) {
			fRec123[l150] = 0.0f;
		}
		for (int l151 = 0; l151 < 2; l151 = l151 + 1) {
			fVec42[l151] = 0.0f;
		}
		for (int l152 = 0; l152 < 2; l152 = l152 + 1) {
			fRec116[l152] = 0.0f;
		}
		for (int l153 = 0; l153 < 2; l153 = l153 + 1) {
			fRec114[l153] = 0.0f;
		}
		for (int l154 = 0; l154 < 2; l154 = l154 + 1) {
			fRec125[l154] = 0.0f;
		}
		for (int l155 = 0; l155 < 16384; l155 = l155 + 1) {
			fVec43[l155] = 0.0f;
		}
		for (int l156 = 0; l156 < 2; l156 = l156 + 1) {
			fVec44[l156] = 0.0f;
		}
		for (int l157 = 0; l157 < 2; l157 = l157 + 1) {
			fRec124[l157] = 0.0f;
		}
		for (int l158 = 0; l158 < 2; l158 = l158 + 1) {
			fRec115[l158] = 0.0f;
		}
		for (int l159 = 0; l159 < 16384; l159 = l159 + 1) {
			fVec45[l159] = 0.0f;
		}
		for (int l160 = 0; l160 < 2; l160 = l160 + 1) {
			fRec126[l160] = 0.0f;
		}
		for (int l161 = 0; l161 < 2; l161 = l161 + 1) {
			fVec46[l161] = 0.0f;
		}
		for (int l162 = 0; l162 < 2; l162 = l162 + 1) {
			fRec113[l162] = 0.0f;
		}
		for (int l163 = 0; l163 < 2; l163 = l163 + 1) {
			fRec111[l163] = 0.0f;
		}
		for (int l164 = 0; l164 < 2; l164 = l164 + 1) {
			fRec128[l164] = 0.0f;
		}
		for (int l165 = 0; l165 < 16384; l165 = l165 + 1) {
			fVec47[l165] = 0.0f;
		}
		for (int l166 = 0; l166 < 2; l166 = l166 + 1) {
			fVec48[l166] = 0.0f;
		}
		for (int l167 = 0; l167 < 2; l167 = l167 + 1) {
			fRec127[l167] = 0.0f;
		}
		for (int l168 = 0; l168 < 2; l168 = l168 + 1) {
			fRec112[l168] = 0.0f;
		}
		for (int l169 = 0; l169 < 16384; l169 = l169 + 1) {
			fVec49[l169] = 0.0f;
		}
		for (int l170 = 0; l170 < 2; l170 = l170 + 1) {
			fRec129[l170] = 0.0f;
		}
		for (int l171 = 0; l171 < 2; l171 = l171 + 1) {
			fVec50[l171] = 0.0f;
		}
		for (int l172 = 0; l172 < 2; l172 = l172 + 1) {
			fRec110[l172] = 0.0f;
		}
		for (int l173 = 0; l173 < 2; l173 = l173 + 1) {
			fRec108[l173] = 0.0f;
		}
		for (int l174 = 0; l174 < 2; l174 = l174 + 1) {
			fRec131[l174] = 0.0f;
		}
		for (int l175 = 0; l175 < 16384; l175 = l175 + 1) {
			fVec51[l175] = 0.0f;
		}
		for (int l176 = 0; l176 < 2; l176 = l176 + 1) {
			fVec52[l176] = 0.0f;
		}
		for (int l177 = 0; l177 < 2; l177 = l177 + 1) {
			fRec130[l177] = 0.0f;
		}
		for (int l178 = 0; l178 < 2; l178 = l178 + 1) {
			fRec109[l178] = 0.0f;
		}
		for (int l179 = 0; l179 < 2; l179 = l179 + 1) {
			fRec46[l179] = 0.0f;
		}
		for (int l180 = 0; l180 < 1024; l180 = l180 + 1) {
			fRec44[l180] = 0.0f;
		}
		for (int l181 = 0; l181 < 2; l181 = l181 + 1) {
			fRec132[l181] = 0.0f;
		}
		for (int l182 = 0; l182 < 1024; l182 = l182 + 1) {
			fRec45[l182] = 0.0f;
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
		ui_interface->openVerticalBox("UrsynthForExport");
		ui_interface->openHorizontalBox("adsr");
		ui_interface->addHorizontalSlider("attack", &fHslider1, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.01f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("decay", &fHslider2, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(7.0f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("release", &fHslider0, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("every");
		ui_interface->openVerticalBox("Basic");
		ui_interface->declare(&fHslider3, "1", "");
		ui_interface->addHorizontalSlider("freq", &fHslider3, FAUSTFLOAT(2e+02f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+03f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider7, "2", "");
		ui_interface->addHorizontalSlider("gain", &fHslider7, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider6, "3", "");
		ui_interface->addHorizontalSlider("index", &fHslider6, FAUSTFLOAT(0.65f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider5, "3", "");
		ui_interface->addHorizontalSlider("index2", &fHslider5, FAUSTFLOAT(0.95f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider4, "3", "");
		ui_interface->addHorizontalSlider("index3", &fHslider4, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fCheckbox1, "4", "");
		ui_interface->addCheckButton("gate", &fCheckbox1);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("moog");
		ui_interface->addVerticalSlider("fr", &fVslider6, FAUSTFLOAT(2e+02f), FAUSTFLOAT(2e+02f), FAUSTFLOAT(4e+03f), FAUSTFLOAT(0.001f));
		ui_interface->addVerticalSlider("fr2", &fVslider4, FAUSTFLOAT(2e+03f), FAUSTFLOAT(2e+02f), FAUSTFLOAT(4e+03f), FAUSTFLOAT(0.001f));
		ui_interface->addVerticalSlider("fr3", &fVslider2, FAUSTFLOAT(2e+03f), FAUSTFLOAT(2e+02f), FAUSTFLOAT(4e+03f), FAUSTFLOAT(0.001f));
		ui_interface->addVerticalSlider("fr4", &fVslider0, FAUSTFLOAT(2e+03f), FAUSTFLOAT(2e+02f), FAUSTFLOAT(4e+03f), FAUSTFLOAT(0.001f));
		ui_interface->addVerticalSlider("res", &fVslider7, FAUSTFLOAT(0.7f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->addVerticalSlider("res2", &fVslider5, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->addVerticalSlider("res3", &fVslider3, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->addVerticalSlider("res4", &fVslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("damp", &fHslider10, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("dt", &fHslider14, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.1f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("earlydiff", &fHslider15, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("feedback", &fHslider11, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("moddepth", &fHslider13, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("modfreq", &fHslider12, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->addCheckButton("select", &fCheckbox0);
		ui_interface->addHorizontalSlider("size", &fHslider16, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.5f), FAUSTFLOAT(3.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("trem", &fHslider8, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(0.1f));
		ui_interface->addHorizontalSlider("wetdrymix", &fHslider9, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		int iSlow0 = int(float(fCheckbox0));
		int iSlow1 = float(fCheckbox1) > 0.0f;
		float fSlow2 = float(fHslider0);
		float fSlow3 = float(fHslider1);
		int iSlow4 = int(fConst0 * fSlow3);
		float fSlow5 = float(fHslider2);
		float fSlow6 = float(iSlow1);
		float fSlow7 = 0.9f * fSlow6;
		float fSlow8 = fConst2 * float(fVslider0);
		float fSlow9 = fConst2 * float(fVslider1);
		float fSlow10 = fConst2 * float(fHslider3);
		float fSlow11 = fConst2 * float(fHslider4);
		float fSlow12 = fConst2 * float(fVslider2);
		float fSlow13 = fConst2 * float(fVslider3);
		float fSlow14 = fConst2 * float(fHslider5);
		float fSlow15 = fConst2 * float(fVslider4);
		float fSlow16 = fConst2 * float(fVslider5);
		float fSlow17 = fConst2 * float(fHslider6);
		float fSlow18 = fConst2 * float(fVslider6);
		float fSlow19 = fConst2 * float(fVslider7);
		float fSlow20 = 0.5f * float(fHslider7);
		float fSlow21 = fConst1 * float(fHslider8);
		float fSlow22 = fConst2 * float(fHslider9);
		float fSlow23 = fConst2 * float(fHslider10);
		float fSlow24 = fConst2 * float(fHslider11);
		float fSlow25 = fConst2 * float(fHslider12);
		float fSlow26 = fConst2 * float(fHslider13);
		float fSlow27 = fConst2 * float(fHslider14);
		float fSlow28 = fConst2 * float(fHslider15);
		float fSlow29 = fConst2 * float(fHslider16);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			iVec1[0] = iSlow1;
			int iTemp0 = iSlow1 - iVec1[1];
			iRec1[0] = iSlow1 * (iRec1[1] + 1);
			int iTemp1 = (iRec1[0] < iSlow4) | (iTemp0 * (iTemp0 > 0));
			float fTemp2 = 0.1447178f * ((iSlow1) ? ((iTemp1) ? fSlow3 : fSlow5) : fSlow2);
			int iTemp3 = std::fabs(fTemp2) < 1.1920929e-07f;
			float fTemp4 = ((iTemp3) ? 0.0f : std::exp(-(fConst1 / ((iTemp3) ? 1.0f : fTemp2))));
			fRec0[0] = (1.0f - fTemp4) * ((iSlow1) ? ((iTemp1) ? fSlow6 : fSlow7) : 0.0f) + fTemp4 * fRec0[1];
			fRec3[0] = fSlow8 + fConst3 * fRec3[1];
			float fTemp5 = fConst4 * fRec3[0];
			float fTemp6 = 1.0f - fTemp5;
			fRec8[0] = fSlow9 + fConst3 * fRec8[1];
			fRec11[0] = fSlow10 + fConst3 * fRec11[1];
			float fTemp7 = std::max<float>(1.1920929e-07f, std::fabs(1.0050251f * fRec11[0]));
			float fTemp8 = fConst1 * fTemp7;
			float fTemp9 = fRec9[1] + fTemp8;
			float fTemp10 = fTemp9 + -1.0f;
			int iTemp11 = fTemp10 < 0.0f;
			fRec9[0] = ((iTemp11) ? fTemp9 : fTemp10);
			float fRec10 = ((iTemp11) ? fTemp9 : fRec9[1] + fTemp8 + fTemp10 * (1.0f - fConst0 / fTemp7));
			float fTemp12 = 2.0f * fRec10;
			float fTemp13 = fTemp12 + -1.0f;
			fRec12[0] = fSlow11 + fConst3 * fRec12[1];
			float fTemp14 = std::max<float>(0.0f, std::min<float>(0.99f, fRec12[0]));
			float fTemp15 = std::cos(6.2831855f * (fTemp12 + (-1.0f - std::min<float>(fTemp13, fTemp14 * (1.0f - fTemp13) / (1.0f - fTemp14)))));
			fRec7[0] = 0.25f * fTemp15 + fTemp6 * fRec7[1] - 4.0f * std::max<float>(0.0f, std::min<float>(fRec8[0], 0.999999f)) * fRec2[1];
			fRec6[0] = fRec7[0] + fTemp6 * fRec6[1];
			fRec5[0] = fRec6[0] + fTemp6 * fRec5[1];
			fRec4[0] = fRec5[0] + fRec4[1] * fTemp6;
			fRec2[0] = fRec4[0] * mydsp_faustpower4_f(fTemp5);
			fRec14[0] = fSlow12 + fConst3 * fRec14[1];
			float fTemp16 = fConst4 * fRec14[0];
			float fTemp17 = 1.0f - fTemp16;
			fRec19[0] = fSlow13 + fConst3 * fRec19[1];
			fRec20[0] = fSlow14 + fConst3 * fRec20[1];
			float fTemp18 = std::min<float>(0.5f, std::max<float>(0.01f, 0.5f * (1.0f - fRec20[0])));
			float fTemp19 = 0.5f - fTemp18;
			float fTemp20 = std::max<float>(1.1920929e-07f, std::fabs(0.99502486f * fRec11[0]));
			float fTemp21 = fConst1 * fTemp20;
			float fTemp22 = fRec21[1] + fTemp21;
			float fTemp23 = fTemp22 + -1.0f;
			int iTemp24 = fTemp23 < 0.0f;
			fRec21[0] = ((iTemp24) ? fTemp22 : fTemp23);
			float fRec22 = ((iTemp24) ? fTemp22 : fTemp21 + fRec21[1] + fTemp23 * (1.0f - fConst0 / fTemp20));
			float fTemp25 = 2.0f * fRec22;
			float fTemp26 = fTemp25 + -1.0f;
			float fTemp27 = std::cos(6.2831855f * (fTemp25 + std::min<float>(fTemp26 * fTemp19 / fTemp18, fTemp19 * (1.0f - fTemp26) / (1.0f - fTemp18)) + -1.0f));
			fRec18[0] = 0.25f * fTemp27 + fTemp17 * fRec18[1] - 4.0f * std::max<float>(0.0f, std::min<float>(fRec19[0], 0.999999f)) * fRec13[1];
			fRec17[0] = fRec18[0] + fTemp17 * fRec17[1];
			fRec16[0] = fRec17[0] + fTemp17 * fRec16[1];
			fRec15[0] = fRec16[0] + fRec15[1] * fTemp17;
			fRec13[0] = fRec15[0] * mydsp_faustpower4_f(fTemp16);
			fRec24[0] = fSlow15 + fConst3 * fRec24[1];
			float fTemp28 = fConst4 * fRec24[0];
			float fTemp29 = 1.0f - fTemp28;
			fRec29[0] = fSlow16 + fConst3 * fRec29[1];
			float fTemp30 = std::max<float>(1.1920929e-07f, std::fabs(0.9876543f * fRec11[0]));
			float fTemp31 = fRec30[1] + fConst1 * fTemp30;
			float fTemp32 = fTemp31 + -1.0f;
			int iTemp33 = fTemp32 < 0.0f;
			fRec30[0] = ((iTemp33) ? fTemp31 : fTemp32);
			float fRec31 = ((iTemp33) ? fTemp31 : fTemp31 + fTemp32 * (1.0f - fConst0 / fTemp30));
			float fTemp34 = 2.0f * fRec31 + -1.0f;
			float fTemp35 = 2.0f * fTemp34;
			float fTemp36 = std::floor(fTemp35 + 1.0f);
			float fTemp37 = fTemp35 + (1.0f - fTemp36);
			fRec32[0] = fSlow17 + fConst3 * fRec32[1];
			float fTemp38 = std::min<float>(1.0f, std::max<float>(0.0f, std::sqrt(std::sqrt(fRec32[0]))));
			float fTemp39 = std::cos(3.1415927f * (float(fTemp34 >= 0.5f) + fTemp35 + (1.0f - (fTemp36 + std::min<float>(fTemp37, fTemp38 * (1.0f - fTemp37) / (1.0f - fTemp38))))));
			fRec28[0] = 0.25f * fTemp39 + fTemp29 * fRec28[1] - 4.0f * std::max<float>(0.0f, std::min<float>(fRec29[0], 0.999999f)) * fRec23[1];
			fRec27[0] = fRec28[0] + fTemp29 * fRec27[1];
			fRec26[0] = fRec27[0] + fTemp29 * fRec26[1];
			fRec25[0] = fRec26[0] + fRec25[1] * fTemp29;
			fRec23[0] = fRec25[0] * mydsp_faustpower4_f(fTemp28);
			fRec34[0] = fSlow18 + fConst3 * fRec34[1];
			float fTemp40 = fConst4 * fRec34[0];
			float fTemp41 = 1.0f - fTemp40;
			fRec39[0] = fSlow19 + fConst3 * fRec39[1];
			int iTemp42 = 1 - iVec0[1];
			float fTemp43 = ((iTemp42) ? 0.0f : fRec41[1] + fConst1 * fRec11[0]);
			fRec41[0] = fTemp43 - std::floor(fTemp43);
			fRec38[0] = 0.25f * (fTemp39 + fTemp27 + fTemp15) + fTemp41 * fRec38[1] + ftbl0mydspSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec41[0]), 65535))] - 4.0f * std::max<float>(0.0f, std::min<float>(fRec39[0], 0.999999f)) * fRec33[1];
			fRec37[0] = fRec38[0] + fTemp41 * fRec37[1];
			fRec36[0] = fRec37[0] + fTemp41 * fRec36[1];
			fRec35[0] = fRec36[0] + fRec35[1] * fTemp41;
			fRec33[0] = fRec35[0] * mydsp_faustpower4_f(fTemp40);
			float fTemp44 = (fRec33[0] + fRec23[0] + fRec13[0] + fRec2[0]) * fRec0[0];
			float fTemp45 = ((iTemp42) ? 0.0f : fSlow21 + fRec42[1]);
			fRec42[0] = fTemp45 - std::floor(fTemp45);
			float fTemp46 = ((iSlow0) ? fSlow20 * fTemp44 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec42[0]), 65535))] : fSlow20 * fTemp44);
			fRec43[0] = fSlow22 + fConst3 * fRec43[1];
			float fTemp47 = (1.0f - fRec43[0]) * fTemp46;
			fRec47[0] = fSlow23 + fConst3 * fRec47[1];
			float fTemp48 = fRec47[0] + fRec47[1];
			fRec48[0] = fSlow24 + fConst3 * fRec48[1];
			float fTemp49 = fRec48[0] + fRec48[1];
			fRec51[0] = fSlow25 + fConst3 * fRec51[1];
			float fTemp50 = fConst5 * (fRec51[0] + fRec51[1]);
			float fTemp51 = std::cos(fTemp50);
			float fTemp52 = std::sin(fTemp50);
			fRec49[0] = fRec50[1] * fTemp52 + fRec49[1] * fTemp51;
			fRec50[0] = float(iTemp42) + fRec50[1] * fTemp51 - fTemp52 * fRec49[1];
			fRec52[0] = fSlow26 + fConst3 * fRec52[1];
			float fTemp53 = fRec52[0] + fRec52[1];
			float fTemp54 = fConst6 * fTemp53 * (fRec50[0] + 1.0f);
			float fTemp55 = fTemp54 + 8.500005f;
			int iTemp56 = int(fTemp55);
			float fTemp57 = std::floor(fTemp55);
			float fTemp58 = fTemp54 + (7.0f - fTemp57);
			float fTemp59 = fTemp54 + (8.0f - fTemp57);
			float fTemp60 = fTemp54 + (9.0f - fTemp57);
			float fTemp61 = fTemp54 + (1e+01f - fTemp57);
			float fTemp62 = fTemp61 * fTemp60;
			float fTemp63 = fTemp62 * fTemp59;
			float fTemp64 = (fTemp54 + (6.0f - fTemp57)) * (fTemp58 * (fTemp59 * (0.041666668f * fRec44[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp56)) + 1)) & 1023] * fTemp60 - 0.16666667f * fTemp61 * fRec44[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp56 + 1)) + 1)) & 1023]) + 0.25f * fTemp62 * fRec44[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp56 + 2)) + 1)) & 1023]) - 0.16666667f * fTemp63 * fRec44[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp56 + 3)) + 1)) & 1023]) + 0.041666668f * fTemp63 * fTemp58 * fRec44[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp56 + 4)) + 1)) & 1023];
			fVec3[IOTA0 & 131071] = fTemp64;
			fRec57[0] = fSlow27 + fConst3 * fRec57[1];
			float fTemp65 = std::floor(std::min<float>(65533.0f, fConst0 * fRec57[0]));
			float fTemp66 = ((fRec53[1] != 0.0f) ? (((fRec54[1] > 0.0f) & (fRec54[1] < 1.0f)) ? fRec53[1] : 0.0f) : (((fRec54[1] == 0.0f) & (fTemp65 != fRec55[1])) ? 4.5351473e-05f : (((fRec54[1] == 1.0f) & (fTemp65 != fRec56[1])) ? -4.5351473e-05f : 0.0f)));
			fRec53[0] = fTemp66;
			fRec54[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec54[1] + fTemp66));
			fRec55[0] = (((fRec54[1] >= 1.0f) & (fRec56[1] != fTemp65)) ? fTemp65 : fRec55[1]);
			fRec56[0] = (((fRec54[1] <= 0.0f) & (fRec55[1] != fTemp65)) ? fTemp65 : fRec56[1]);
			int iTemp67 = int(std::min<float>(65536.0f, std::max<float>(0.0f, fRec55[0])));
			float fTemp68 = fVec3[(IOTA0 - iTemp67) & 131071];
			int iTemp69 = int(std::min<float>(65536.0f, std::max<float>(0.0f, fRec56[0])));
			float fTemp70 = 0.5f * (fTemp68 + fRec54[0] * (fVec3[(IOTA0 - iTemp69) & 131071] - fTemp68)) * fTemp49 + fTemp46;
			fRec58[0] = fSlow28 + fConst3 * fRec58[1];
			float fTemp71 = fRec58[0] + fRec58[1];
			float fTemp72 = 0.5f * fTemp71;
			float fTemp73 = std::sin(fTemp72);
			float fTemp74 = std::cos(fTemp72);
			float fTemp75 = fConst6 * fTemp53 * (fRec49[0] + 1.0f);
			float fTemp76 = fTemp75 + 8.500005f;
			int iTemp77 = int(fTemp76);
			float fTemp78 = std::floor(fTemp76);
			float fTemp79 = fTemp75 + (7.0f - fTemp78);
			float fTemp80 = fTemp75 + (8.0f - fTemp78);
			float fTemp81 = fTemp75 + (9.0f - fTemp78);
			float fTemp82 = fTemp75 + (1e+01f - fTemp78);
			float fTemp83 = fTemp82 * fTemp81;
			float fTemp84 = fTemp83 * fTemp80;
			float fTemp85 = (fTemp75 + (6.0f - fTemp78)) * (fTemp79 * (fTemp80 * (0.041666668f * fRec45[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp77)) + 1)) & 1023] * fTemp81 - 0.16666667f * fTemp82 * fRec45[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp77 + 1)) + 1)) & 1023]) + 0.25f * fTemp83 * fRec45[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp77 + 2)) + 1)) & 1023]) - 0.16666667f * fTemp84 * fRec45[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp77 + 3)) + 1)) & 1023]) + 0.041666668f * fTemp84 * fTemp79 * fRec45[(IOTA0 - (std::min<int>(512, std::max<int>(0, iTemp77 + 4)) + 1)) & 1023];
			fVec4[IOTA0 & 131071] = fTemp85;
			float fTemp86 = fVec4[(IOTA0 - iTemp67) & 131071];
			float fTemp87 = fTemp46 + 0.5f * fTemp49 * (fTemp86 + fRec54[0] * (fVec4[(IOTA0 - iTemp69) & 131071] - fTemp86));
			float fTemp88 = fTemp74 * fTemp87 - fTemp73 * fRec60[1];
			float fTemp89 = fTemp74 * fTemp88 - fTemp73 * fRec63[1];
			float fTemp90 = fTemp74 * fTemp89 - fTemp73 * fRec66[1];
			fRec72[0] = fSlow29 + fConst3 * fRec72[1];
			int iTemp91 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(49.0f * fRec72[0]), 1301))];
			fRec71[0] = 0.9999f * (fRec71[1] + float(iTemp42 * iTemp91)) + 0.0001f * float(iTemp91);
			float fTemp92 = fRec71[0] + -1.49999f;
			float fTemp93 = std::floor(fTemp92);
			fVec5[IOTA0 & 16383] = fTemp73 * fRec69[1] - fTemp74 * fTemp90;
			float fTemp94 = fVec5[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp92)))) & 16383];
			fVec6[0] = fTemp94;
			fRec70[0] = fVec6[1] - (fTemp93 + (2.0f - fRec71[0])) * (fRec70[1] - fTemp94) / (fRec71[0] - fTemp93);
			fRec68[0] = fRec70[0];
			int iTemp95 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(59.0f * fRec72[0]), 1301))];
			fRec74[0] = 0.9999f * (fRec74[1] + float(iTemp42 * iTemp95)) + 0.0001f * float(iTemp95);
			float fTemp96 = fRec74[0] + -1.49999f;
			float fTemp97 = std::floor(fTemp96);
			float fTemp98 = fTemp70 * fTemp74 - fTemp73 * fRec59[1];
			float fTemp99 = fTemp74 * fTemp98 - fTemp73 * fRec62[1];
			float fTemp100 = fTemp74 * fTemp99 - fTemp73 * fRec65[1];
			fVec7[IOTA0 & 16383] = fTemp74 * fTemp100 - fTemp73 * fRec68[1];
			float fTemp101 = fVec7[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp96)))) & 16383];
			fVec8[0] = fTemp101;
			fRec73[0] = fVec8[1] - (fTemp97 + (2.0f - fRec74[0])) * (fRec73[1] - fTemp101) / (fRec74[0] - fTemp97);
			fRec69[0] = fRec73[0];
			fVec9[IOTA0 & 16383] = fTemp74 * fRec69[1] + fTemp73 * fTemp90;
			int iTemp102 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(36.0f * fRec72[0]), 1301))];
			fRec75[0] = 0.9999f * (fRec75[1] + float(iTemp42 * iTemp102)) + 0.0001f * float(iTemp102);
			float fTemp103 = fRec75[0] + -1.49999f;
			float fTemp104 = fVec9[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp103)))) & 16383];
			fVec10[0] = fTemp104;
			float fTemp105 = std::floor(fTemp103);
			float fTemp106 = fRec75[0] - fTemp105;
			float fTemp107 = fTemp105 + (2.0f - fRec75[0]);
			fRec67[0] = -(fRec67[1] * fTemp107 / fTemp106 + fTemp107 * fTemp104 / fTemp106 + fVec10[1]);
			fRec65[0] = fRec67[0];
			int iTemp108 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(46.0f * fRec72[0]), 1301))];
			fRec77[0] = 0.9999f * (fRec77[1] + float(iTemp42 * iTemp108)) + 0.0001f * float(iTemp108);
			float fTemp109 = fRec77[0] + -1.49999f;
			float fTemp110 = std::floor(fTemp109);
			fVec11[IOTA0 & 16383] = fRec68[1] * fTemp74 + fTemp73 * fTemp100;
			float fTemp111 = fVec11[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp109)))) & 16383];
			fVec12[0] = fTemp111;
			fRec76[0] = fVec12[1] + (fTemp110 + (2.0f - fRec77[0])) * (fTemp111 - fRec76[1]) / (fRec77[0] - fTemp110);
			fRec66[0] = fRec76[0];
			fVec13[IOTA0 & 16383] = fTemp74 * fRec66[1] + fTemp73 * fTemp89;
			int iTemp112 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(23.0f * fRec72[0]), 1301))];
			fRec78[0] = 0.9999f * (fRec78[1] + float(iTemp42 * iTemp112)) + 0.0001f * float(iTemp112);
			float fTemp113 = fRec78[0] + -1.49999f;
			float fTemp114 = fVec13[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp113)))) & 16383];
			fVec14[0] = fTemp114;
			float fTemp115 = std::floor(fTemp113);
			float fTemp116 = fRec78[0] - fTemp115;
			float fTemp117 = fTemp115 + (2.0f - fRec78[0]);
			fRec64[0] = -(fRec64[1] * fTemp117 / fTemp116 + fTemp117 * fTemp114 / fTemp116 + fVec14[1]);
			fRec62[0] = fRec64[0];
			int iTemp118 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(33.0f * fRec72[0]), 1301))];
			fRec80[0] = 0.9999f * (fRec80[1] + float(iTemp42 * iTemp118)) + 0.0001f * float(iTemp118);
			float fTemp119 = fRec80[0] + -1.49999f;
			float fTemp120 = std::floor(fTemp119);
			fVec15[IOTA0 & 16383] = fRec65[1] * fTemp74 + fTemp73 * fTemp99;
			float fTemp121 = fVec15[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp119)))) & 16383];
			fVec16[0] = fTemp121;
			fRec79[0] = fVec16[1] - (fTemp120 + (2.0f - fRec80[0])) * (fRec79[1] - fTemp121) / (fRec80[0] - fTemp120);
			fRec63[0] = fRec79[0];
			fVec17[IOTA0 & 16383] = fTemp74 * fRec63[1] + fTemp73 * fTemp88;
			int iTemp122 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(1e+01f * fRec72[0]), 1301))];
			fRec81[0] = 0.9999f * (fRec81[1] + float(iTemp42 * iTemp122)) + 0.0001f * float(iTemp122);
			float fTemp123 = fRec81[0] + -1.49999f;
			float fTemp124 = fVec17[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp123)))) & 16383];
			fVec18[0] = fTemp124;
			float fTemp125 = std::floor(fTemp123);
			float fTemp126 = fRec81[0] - fTemp125;
			float fTemp127 = fTemp125 + (2.0f - fRec81[0]);
			fRec61[0] = -(fRec61[1] * fTemp127 / fTemp126 + fTemp127 * fTemp124 / fTemp126 + fVec18[1]);
			fRec59[0] = fRec61[0];
			int iTemp128 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(2e+01f * fRec72[0]), 1301))];
			fRec83[0] = 0.9999f * (fRec83[1] + float(iTemp42 * iTemp128)) + 0.0001f * float(iTemp128);
			float fTemp129 = fRec83[0] + -1.49999f;
			float fTemp130 = std::floor(fTemp129);
			fVec19[IOTA0 & 16383] = fRec62[1] * fTemp74 + fTemp73 * fTemp98;
			float fTemp131 = fVec19[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp129)))) & 16383];
			fVec20[0] = fTemp131;
			fRec82[0] = fVec20[1] + (fTemp130 + (2.0f - fRec83[0])) * (fTemp131 - fRec82[1]) / (fRec83[0] - fTemp130);
			fRec60[0] = fRec82[0];
			float fTemp132 = fRec59[1] * fTemp74 + fTemp73 * fTemp70;
			float fTemp133 = -0.5f * fTemp71;
			float fTemp134 = std::sin(fTemp133);
			float fTemp135 = std::cos(fTemp133);
			float fTemp136 = fTemp74 * fRec60[1] + fTemp73 * fTemp87;
			float fTemp137 = fTemp135 * fTemp136 - fTemp134 * fRec85[1];
			float fTemp138 = fTemp135 * fTemp137 - fTemp134 * fRec88[1];
			float fTemp139 = fTemp135 * fTemp138 - fTemp134 * fRec91[1];
			int iTemp140 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(68.0f * fRec72[0]), 1301))];
			fRec96[0] = 0.9999f * (fRec96[1] + float(iTemp42 * iTemp140)) + 0.0001f * float(iTemp140);
			float fTemp141 = fRec96[0] + -1.49999f;
			float fTemp142 = std::floor(fTemp141);
			fVec21[IOTA0 & 16383] = fTemp134 * fRec94[1] - fTemp135 * fTemp139;
			float fTemp143 = fVec21[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp141)))) & 16383];
			fVec22[0] = fTemp143;
			fRec95[0] = fVec22[1] - (fTemp142 + (2.0f - fRec96[0])) * (fRec95[1] - fTemp143) / (fRec96[0] - fTemp142);
			fRec93[0] = fRec95[0];
			int iTemp144 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(78.0f * fRec72[0]), 1301))];
			fRec98[0] = 0.9999f * (fRec98[1] + float(iTemp42 * iTemp144)) + 0.0001f * float(iTemp144);
			float fTemp145 = fRec98[0] + -1.49999f;
			float fTemp146 = std::floor(fTemp145);
			float fTemp147 = fTemp132 * fTemp135 - fTemp134 * fRec84[1];
			float fTemp148 = fTemp135 * fTemp147 - fTemp134 * fRec87[1];
			float fTemp149 = fTemp135 * fTemp148 - fTemp134 * fRec90[1];
			fVec23[IOTA0 & 16383] = fTemp135 * fTemp149 - fRec93[1] * fTemp134;
			float fTemp150 = fVec23[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp145)))) & 16383];
			fVec24[0] = fTemp150;
			fRec97[0] = fVec24[1] - (fTemp146 + (2.0f - fRec98[0])) * (fRec97[1] - fTemp150) / (fRec98[0] - fTemp146);
			fRec94[0] = fRec97[0];
			fVec25[IOTA0 & 16383] = fTemp135 * fRec94[1] + fTemp134 * fTemp139;
			int iTemp151 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(55.0f * fRec72[0]), 1301))];
			fRec99[0] = 0.9999f * (fRec99[1] + float(iTemp42 * iTemp151)) + 0.0001f * float(iTemp151);
			float fTemp152 = fRec99[0] + -1.49999f;
			float fTemp153 = fVec25[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp152)))) & 16383];
			fVec26[0] = fTemp153;
			float fTemp154 = std::floor(fTemp152);
			float fTemp155 = fRec99[0] - fTemp154;
			float fTemp156 = fTemp154 + (2.0f - fRec99[0]);
			fRec92[0] = -(fRec92[1] * fTemp156 / fTemp155 + fTemp156 * fTemp153 / fTemp155 + fVec26[1]);
			fRec90[0] = fRec92[0];
			int iTemp157 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(65.0f * fRec72[0]), 1301))];
			fRec101[0] = 0.9999f * (fRec101[1] + float(iTemp42 * iTemp157)) + 0.0001f * float(iTemp157);
			float fTemp158 = fRec101[0] + -1.49999f;
			float fTemp159 = std::floor(fTemp158);
			fVec27[IOTA0 & 16383] = fRec93[1] * fTemp135 + fTemp134 * fTemp149;
			float fTemp160 = fVec27[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp158)))) & 16383];
			fVec28[0] = fTemp160;
			fRec100[0] = fVec28[1] + (fTemp159 + (2.0f - fRec101[0])) * (fTemp160 - fRec100[1]) / (fRec101[0] - fTemp159);
			fRec91[0] = fRec100[0];
			fVec29[IOTA0 & 16383] = fTemp135 * fRec91[1] + fTemp134 * fTemp138;
			int iTemp161 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(42.0f * fRec72[0]), 1301))];
			fRec102[0] = 0.9999f * (fRec102[1] + float(iTemp42 * iTemp161)) + 0.0001f * float(iTemp161);
			float fTemp162 = fRec102[0] + -1.49999f;
			float fTemp163 = fVec29[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp162)))) & 16383];
			fVec30[0] = fTemp163;
			float fTemp164 = std::floor(fTemp162);
			float fTemp165 = fRec102[0] - fTemp164;
			float fTemp166 = fTemp164 + (2.0f - fRec102[0]);
			fRec89[0] = -(fRec89[1] * fTemp166 / fTemp165 + fTemp166 * fTemp163 / fTemp165 + fVec30[1]);
			fRec87[0] = fRec89[0];
			int iTemp167 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(52.0f * fRec72[0]), 1301))];
			fRec104[0] = 0.9999f * (fRec104[1] + float(iTemp42 * iTemp167)) + 0.0001f * float(iTemp167);
			float fTemp168 = fRec104[0] + -1.49999f;
			float fTemp169 = std::floor(fTemp168);
			fVec31[IOTA0 & 16383] = fRec90[1] * fTemp135 + fTemp134 * fTemp148;
			float fTemp170 = fVec31[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp168)))) & 16383];
			fVec32[0] = fTemp170;
			fRec103[0] = fVec32[1] - (fTemp169 + (2.0f - fRec104[0])) * (fRec103[1] - fTemp170) / (fRec104[0] - fTemp169);
			fRec88[0] = fRec103[0];
			fVec33[IOTA0 & 16383] = fTemp135 * fRec88[1] + fTemp134 * fTemp137;
			int iTemp171 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(29.0f * fRec72[0]), 1301))];
			fRec105[0] = 0.9999f * (fRec105[1] + float(iTemp42 * iTemp171)) + 0.0001f * float(iTemp171);
			float fTemp172 = fRec105[0] + -1.49999f;
			float fTemp173 = fVec33[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp172)))) & 16383];
			fVec34[0] = fTemp173;
			float fTemp174 = std::floor(fTemp172);
			float fTemp175 = fRec105[0] - fTemp174;
			float fTemp176 = fTemp174 + (2.0f - fRec105[0]);
			fRec86[0] = -(fRec86[1] * fTemp176 / fTemp175 + fTemp176 * fTemp173 / fTemp175 + fVec34[1]);
			fRec84[0] = fRec86[0];
			int iTemp177 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(39.0f * fRec72[0]), 1301))];
			fRec107[0] = 0.9999f * (fRec107[1] + float(iTemp42 * iTemp177)) + 0.0001f * float(iTemp177);
			float fTemp178 = fRec107[0] + -1.49999f;
			float fTemp179 = std::floor(fTemp178);
			fVec35[IOTA0 & 16383] = fRec87[1] * fTemp135 + fTemp134 * fTemp147;
			float fTemp180 = fVec35[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp178)))) & 16383];
			fVec36[0] = fTemp180;
			fRec106[0] = fVec36[1] + (fTemp179 + (2.0f - fRec107[0])) * (fTemp180 - fRec106[1]) / (fRec107[0] - fTemp179);
			fRec85[0] = fRec106[0];
			float fTemp181 = fRec84[1] * fTemp135 + fTemp134 * fTemp132;
			float fTemp182 = fTemp135 * fRec85[1] + fTemp134 * fTemp136;
			float fTemp183 = fTemp74 * fTemp182 - fTemp73 * fRec109[1];
			float fTemp184 = fTemp74 * fTemp183 - fTemp73 * fRec112[1];
			float fTemp185 = fTemp74 * fTemp184 - fTemp73 * fRec115[1];
			int iTemp186 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(87.0f * fRec72[0]), 1301))];
			fRec120[0] = 0.9999f * (fRec120[1] + float(iTemp42 * iTemp186)) + 0.0001f * float(iTemp186);
			float fTemp187 = fRec120[0] + -1.49999f;
			float fTemp188 = std::floor(fTemp187);
			fVec37[IOTA0 & 16383] = fTemp73 * fRec118[1] - fTemp74 * fTemp185;
			float fTemp189 = fVec37[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp187)))) & 16383];
			fVec38[0] = fTemp189;
			fRec119[0] = fVec38[1] - (fTemp188 + (2.0f - fRec120[0])) * (fRec119[1] - fTemp189) / (fRec120[0] - fTemp188);
			fRec117[0] = fRec119[0];
			int iTemp190 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(97.0f * fRec72[0]), 1301))];
			fRec122[0] = 0.9999f * (fRec122[1] + float(iTemp42 * iTemp190)) + 0.0001f * float(iTemp190);
			float fTemp191 = fRec122[0] + -1.49999f;
			float fTemp192 = std::floor(fTemp191);
			float fTemp193 = fTemp74 * fTemp181 - fTemp73 * fRec108[1];
			float fTemp194 = fTemp74 * fTemp193 - fTemp73 * fRec111[1];
			float fTemp195 = fTemp74 * fTemp194 - fTemp73 * fRec114[1];
			fVec39[IOTA0 & 16383] = fTemp74 * fTemp195 - fRec117[1] * fTemp73;
			float fTemp196 = fVec39[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp191)))) & 16383];
			fVec40[0] = fTemp196;
			fRec121[0] = fVec40[1] - (fTemp192 + (2.0f - fRec122[0])) * (fRec121[1] - fTemp196) / (fRec122[0] - fTemp192);
			fRec118[0] = fRec121[0];
			fVec41[IOTA0 & 16383] = fTemp74 * fRec118[1] + fTemp73 * fTemp185;
			int iTemp197 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(74.0f * fRec72[0]), 1301))];
			fRec123[0] = 0.9999f * (fRec123[1] + float(iTemp42 * iTemp197)) + 0.0001f * float(iTemp197);
			float fTemp198 = fRec123[0] + -1.49999f;
			float fTemp199 = fVec41[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp198)))) & 16383];
			fVec42[0] = fTemp199;
			float fTemp200 = std::floor(fTemp198);
			float fTemp201 = fRec123[0] - fTemp200;
			float fTemp202 = fTemp200 + (2.0f - fRec123[0]);
			fRec116[0] = -(fRec116[1] * fTemp202 / fTemp201 + fTemp202 * fTemp199 / fTemp201 + fVec42[1]);
			fRec114[0] = fRec116[0];
			int iTemp203 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(84.0f * fRec72[0]), 1301))];
			fRec125[0] = 0.9999f * (fRec125[1] + float(iTemp42 * iTemp203)) + 0.0001f * float(iTemp203);
			float fTemp204 = fRec125[0] + -1.49999f;
			float fTemp205 = std::floor(fTemp204);
			fVec43[IOTA0 & 16383] = fRec117[1] * fTemp74 + fTemp73 * fTemp195;
			float fTemp206 = fVec43[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp204)))) & 16383];
			fVec44[0] = fTemp206;
			fRec124[0] = fVec44[1] - (fTemp205 + (2.0f - fRec125[0])) * (fRec124[1] - fTemp206) / (fRec125[0] - fTemp205);
			fRec115[0] = fRec124[0];
			fVec45[IOTA0 & 16383] = fTemp74 * fRec115[1] + fTemp73 * fTemp184;
			int iTemp207 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(61.0f * fRec72[0]), 1301))];
			fRec126[0] = 0.9999f * (fRec126[1] + float(iTemp42 * iTemp207)) + 0.0001f * float(iTemp207);
			float fTemp208 = fRec126[0] + -1.49999f;
			float fTemp209 = fVec45[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp208)))) & 16383];
			fVec46[0] = fTemp209;
			float fTemp210 = std::floor(fTemp208);
			float fTemp211 = fRec126[0] - fTemp210;
			float fTemp212 = fTemp210 + (2.0f - fRec126[0]);
			fRec113[0] = -(fRec113[1] * fTemp212 / fTemp211 + fTemp212 * fTemp209 / fTemp211 + fVec46[1]);
			fRec111[0] = fRec113[0];
			int iTemp213 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(71.0f * fRec72[0]), 1301))];
			fRec128[0] = 0.9999f * (fRec128[1] + float(iTemp42 * iTemp213)) + 0.0001f * float(iTemp213);
			float fTemp214 = fRec128[0] + -1.49999f;
			float fTemp215 = std::floor(fTemp214);
			fVec47[IOTA0 & 16383] = fRec114[1] * fTemp74 + fTemp73 * fTemp194;
			float fTemp216 = fVec47[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp214)))) & 16383];
			fVec48[0] = fTemp216;
			fRec127[0] = fVec48[1] + (fTemp215 + (2.0f - fRec128[0])) * (fTemp216 - fRec127[1]) / (fRec128[0] - fTemp215);
			fRec112[0] = fRec127[0];
			fVec49[IOTA0 & 16383] = fTemp74 * fRec112[1] + fTemp73 * fTemp183;
			int iTemp217 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(48.0f * fRec72[0]), 1301))];
			fRec129[0] = 0.9999f * (fRec129[1] + float(iTemp42 * iTemp217)) + 0.0001f * float(iTemp217);
			float fTemp218 = fRec129[0] + -1.49999f;
			float fTemp219 = fVec49[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp218)))) & 16383];
			fVec50[0] = fTemp219;
			float fTemp220 = std::floor(fTemp218);
			float fTemp221 = fRec129[0] - fTemp220;
			float fTemp222 = fTemp220 + (2.0f - fRec129[0]);
			fRec110[0] = -(fRec110[1] * fTemp222 / fTemp221 + fTemp222 * fTemp219 / fTemp221 + fVec50[1]);
			fRec108[0] = fRec110[0];
			int iTemp223 = itbl1mydspSIG1[std::max<int>(0, std::min<int>(int(58.0f * fRec72[0]), 1301))];
			fRec131[0] = 0.9999f * (fRec131[1] + float(iTemp42 * iTemp223)) + 0.0001f * float(iTemp223);
			float fTemp224 = fRec131[0] + -1.49999f;
			float fTemp225 = std::floor(fTemp224);
			fVec51[IOTA0 & 16383] = fRec111[1] * fTemp74 + fTemp73 * fTemp193;
			float fTemp226 = fVec51[(IOTA0 - std::min<int>(8192, std::max<int>(0, int(fTemp224)))) & 16383];
			fVec52[0] = fTemp226;
			fRec130[0] = fVec52[1] - (fTemp225 + (2.0f - fRec131[0])) * (fRec130[1] - fTemp226) / (fRec131[0] - fTemp225);
			fRec109[0] = fRec130[0];
			float fTemp227 = 1.0f - 0.5f * fTemp48;
			fRec46[0] = fTemp227 * (fRec108[1] * fTemp74 + fTemp73 * fTemp181) + 0.5f * fTemp48 * fRec46[1];
			fRec44[IOTA0 & 1023] = fRec46[0];
			fRec132[0] = fTemp227 * (fTemp74 * fRec109[1] + fTemp73 * fTemp182) + 0.5f * fTemp48 * fRec132[1];
			fRec45[IOTA0 & 1023] = fRec132[0];
			output0[i0] = FAUSTFLOAT(fRec44[IOTA0 & 1023] * fRec43[0] + fTemp47);
			output1[i0] = FAUSTFLOAT(fTemp47 + fRec43[0] * fRec45[IOTA0 & 1023]);
			iVec0[1] = iVec0[0];
			iVec1[1] = iVec1[0];
			iRec1[1] = iRec1[0];
			fRec0[1] = fRec0[0];
			fRec3[1] = fRec3[0];
			fRec8[1] = fRec8[0];
			fRec11[1] = fRec11[0];
			fRec9[1] = fRec9[0];
			fRec12[1] = fRec12[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec2[1] = fRec2[0];
			fRec14[1] = fRec14[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec13[1] = fRec13[0];
			fRec24[1] = fRec24[0];
			fRec29[1] = fRec29[0];
			fRec30[1] = fRec30[0];
			fRec32[1] = fRec32[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fRec25[1] = fRec25[0];
			fRec23[1] = fRec23[0];
			fRec34[1] = fRec34[0];
			fRec39[1] = fRec39[0];
			fRec41[1] = fRec41[0];
			fRec38[1] = fRec38[0];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec35[1] = fRec35[0];
			fRec33[1] = fRec33[0];
			fRec42[1] = fRec42[0];
			fRec43[1] = fRec43[0];
			fRec47[1] = fRec47[0];
			fRec48[1] = fRec48[0];
			IOTA0 = IOTA0 + 1;
			fRec51[1] = fRec51[0];
			fRec49[1] = fRec49[0];
			fRec50[1] = fRec50[0];
			fRec52[1] = fRec52[0];
			fRec57[1] = fRec57[0];
			fRec53[1] = fRec53[0];
			fRec54[1] = fRec54[0];
			fRec55[1] = fRec55[0];
			fRec56[1] = fRec56[0];
			fRec58[1] = fRec58[0];
			fRec72[1] = fRec72[0];
			fRec71[1] = fRec71[0];
			fVec6[1] = fVec6[0];
			fRec70[1] = fRec70[0];
			fRec68[1] = fRec68[0];
			fRec74[1] = fRec74[0];
			fVec8[1] = fVec8[0];
			fRec73[1] = fRec73[0];
			fRec69[1] = fRec69[0];
			fRec75[1] = fRec75[0];
			fVec10[1] = fVec10[0];
			fRec67[1] = fRec67[0];
			fRec65[1] = fRec65[0];
			fRec77[1] = fRec77[0];
			fVec12[1] = fVec12[0];
			fRec76[1] = fRec76[0];
			fRec66[1] = fRec66[0];
			fRec78[1] = fRec78[0];
			fVec14[1] = fVec14[0];
			fRec64[1] = fRec64[0];
			fRec62[1] = fRec62[0];
			fRec80[1] = fRec80[0];
			fVec16[1] = fVec16[0];
			fRec79[1] = fRec79[0];
			fRec63[1] = fRec63[0];
			fRec81[1] = fRec81[0];
			fVec18[1] = fVec18[0];
			fRec61[1] = fRec61[0];
			fRec59[1] = fRec59[0];
			fRec83[1] = fRec83[0];
			fVec20[1] = fVec20[0];
			fRec82[1] = fRec82[0];
			fRec60[1] = fRec60[0];
			fRec96[1] = fRec96[0];
			fVec22[1] = fVec22[0];
			fRec95[1] = fRec95[0];
			fRec93[1] = fRec93[0];
			fRec98[1] = fRec98[0];
			fVec24[1] = fVec24[0];
			fRec97[1] = fRec97[0];
			fRec94[1] = fRec94[0];
			fRec99[1] = fRec99[0];
			fVec26[1] = fVec26[0];
			fRec92[1] = fRec92[0];
			fRec90[1] = fRec90[0];
			fRec101[1] = fRec101[0];
			fVec28[1] = fVec28[0];
			fRec100[1] = fRec100[0];
			fRec91[1] = fRec91[0];
			fRec102[1] = fRec102[0];
			fVec30[1] = fVec30[0];
			fRec89[1] = fRec89[0];
			fRec87[1] = fRec87[0];
			fRec104[1] = fRec104[0];
			fVec32[1] = fVec32[0];
			fRec103[1] = fRec103[0];
			fRec88[1] = fRec88[0];
			fRec105[1] = fRec105[0];
			fVec34[1] = fVec34[0];
			fRec86[1] = fRec86[0];
			fRec84[1] = fRec84[0];
			fRec107[1] = fRec107[0];
			fVec36[1] = fVec36[0];
			fRec106[1] = fRec106[0];
			fRec85[1] = fRec85[0];
			fRec120[1] = fRec120[0];
			fVec38[1] = fVec38[0];
			fRec119[1] = fRec119[0];
			fRec117[1] = fRec117[0];
			fRec122[1] = fRec122[0];
			fVec40[1] = fVec40[0];
			fRec121[1] = fRec121[0];
			fRec118[1] = fRec118[0];
			fRec123[1] = fRec123[0];
			fVec42[1] = fVec42[0];
			fRec116[1] = fRec116[0];
			fRec114[1] = fRec114[0];
			fRec125[1] = fRec125[0];
			fVec44[1] = fVec44[0];
			fRec124[1] = fRec124[0];
			fRec115[1] = fRec115[0];
			fRec126[1] = fRec126[0];
			fVec46[1] = fVec46[0];
			fRec113[1] = fRec113[0];
			fRec111[1] = fRec111[0];
			fRec128[1] = fRec128[0];
			fVec48[1] = fVec48[0];
			fRec127[1] = fRec127[0];
			fRec112[1] = fRec112[0];
			fRec129[1] = fRec129[0];
			fVec50[1] = fVec50[0];
			fRec110[1] = fRec110[0];
			fRec108[1] = fRec108[0];
			fRec131[1] = fRec131[0];
			fVec52[1] = fVec52[0];
			fRec130[1] = fRec130[0];
			fRec109[1] = fRec109[0];
			fRec46[1] = fRec46[0];
			fRec132[1] = fRec132[0];
		}
	}

};

// END-FAUSTDSP

#endif
