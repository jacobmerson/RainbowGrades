#ifndef _GRADEABLE_H_
#define _GRADEABLE_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cassert>


enum class GRADEABLE_ENUM {
  HOMEWORK, ASSIGNMENT, PROBLEM_SET,
    QUIZ, TEST, EXAM,
    EXERCISE, LECTURE_EXERCISE, READING, WORKSHEET, LAB, RECITATION,
    PROJECT, PARTICIPATION, NOTE,
    NONE };

std::string gradeable_to_string(const GRADEABLE_ENUM &g);

bool string_to_gradeable_enum(const std::string &s, GRADEABLE_ENUM &return_value);

// ===============================================================================

class Gradeable {

public:

  // CONSTRUTORS
  Gradeable() { count=0;percent=0;remove_lowest=0; }
  Gradeable(int c, float p) : count(c),percent(p) { remove_lowest=0; }

  // ACCESSORS
  int getCount() const;
  float getPercent() const;
  float getBucketPercentageUpperClamp() const;
  float getMaximum() const;
  int getRemoveLowest() const;
  std::string getID(int index) const;
  void isResubmit(int index,
                  std::string &original_id, std::string &resubmit_id,
                  float &autograde_replacement_percentage);
  bool hasCorrespondence(const std::string &id) const;
  const std::pair<int,std::string>& getCorrespondence(const std::string& id);
  bool isReleased(const std::string &id) const;
  float getItemMaximum(const std::string &id) const;
  float getScaleMaximum(const std::string &id) const;
  float getItemPercentage(const std::string &id) const;
  float getClamp(const std::string &id) const;
  float getSortedWeight(unsigned int position);
  bool hasSortedWeight();

  // MODIFIERS
  void setRemoveLowest(int r);
  int setCorrespondence(const std::string& id);
  // Set the max percentage that can be received for a gradeable type.
  // If the value is less than 0, it should be ignored.
  void setBucketPercentageUpperClamp(float bucket_percentage_upper_clamp);
  void setCorrespondenceName(const std::string& id, const std::string& name);
  void setReleased(const std::string&id, bool is_released);
  void setMaximum(const std::string&id, float maximum);
  void setScaleMaximum(const std::string&id, float scale_maximum);
  void setItemPercentage(const std::string&id, float item_percentage);
  void setClamp(const std::string&id, float clamp);
  void setResubmissionValues(const std::string &id,
                             const std::string &original_id, const std::string &resubmit_id,
                             const std::string &title,
                             float autograde_replacement_percentage);
  void addSortedWeight(float weight);

private:

  // REPRESENTATION
  int count;
  float percent;
  int remove_lowest;
  float bucket_percentage_upper_clamp;
  std::map<std::string,std::pair<int,std::string> > correspondences;
  std::map<std::string,float> maximums;
  std::map<std::string,float> scale_maximums;
  std::map<std::string,float> item_percentages;
  std::vector<float> sorted_weights;
  std::map<std::string,float> clamps;
  std::map<std::string,bool> released;
  std::map<std::string,std::string> original_ids;
  std::map<std::string,std::string> resubmit_ids;
  std::map<std::string,float> autograde_replacement_percentages;
};

// ===============================================================================

extern std::vector<GRADEABLE_ENUM>    ALL_GRADEABLES;

extern std::map<GRADEABLE_ENUM,Gradeable>  GRADEABLES;


void LookupGradeable(const std::string &id,
                     GRADEABLE_ENUM &g_e, int &i);


#endif
