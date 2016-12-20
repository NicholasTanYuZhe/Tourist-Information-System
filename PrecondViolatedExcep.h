/*************************************
Program: PrecondViolatedExcep.h
Course: OOPDS
Year: 2015/16 Trimester 2
Name: NICHOLAS TAN YU ZHE
ID: 1142701655
Lecture: TC102
Lab: TT04
Email: nicholas.290696@gmail.com
Phone: 016-7768182
*************************************/

#ifndef _PRECOND_VIOLATED_EXCEP
#define _PRECOND_VIOLATED_EXCEP

#include <stdexcept>
#include <string>

using namespace std;

class PrecondViolatedExcep : public logic_error
{
public:
   PrecondViolatedExcep(const string& message = "");
}; // end PrecondViolatedExcep 
#endif
