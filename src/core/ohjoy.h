#ifndef __OHJOY__H__
#define __OHJOY__H__

struct Student {
    int id;
};

/*!
 *@author richard sun
 *@brief search Student info
 *@param id int
 *@param name char*
 *@return id of student
 *@retval int
 *
 */
extern int searchStudent(int id, char* name);

#endif
