class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if(s.length() != t.length()){
            return false;
        }

        unordered_map<char, char> charMap;
        unordered_set<char> registerReplace;

        for(int i = 0; i < s.length(); i++){
            char original = s[i];
            char replacement = t[i];

            if(charMap.find(original) == charMap.end()){
                if(registerReplace.find(replacement) != registerReplace.end()){
                    return false;
                }
                charMap[original] = replacement;
                registerReplace.insert(replacement);
            }
            else{
                if(charMap[original] != replacement){
                    return false;
                }
            }
        }
        return true;
    }
};