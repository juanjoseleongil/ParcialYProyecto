//Program to test class "telegraph"
#include <iostream>
#include <iomanip>
#include "telegraph.h"
#include "example5.h"

#define printIndex std::left << std::setw(2)
#define printReal std::right << std::setw(7) << std::fixed << std::setprecision(4)
#define printComp std::setw(7) << std::scientific << std::setprecision(1)

int main()
{
  /*PACKAGE USER INPUT AS VECTORS*/

  //vector containing endpoints
  std::vector<double> endpoints{t0, tf, z0, zf};

  //vector containing system parameters
  std::vector<double> params{ALPHA, BETA, C2, SIGMA};

  //vector of functions, containing all boundary conditions for voltage
  std::vector<std::function<double(double)>> bcV{v_t0, ddt_v_t0, 
                                                 v_z0, v_zf};

  //vector of functions, containing all boundary conditions for current
  std::vector<std::function<double(double)>> bcI{i_t0, ddt_i_t0, 
                                                 i_z0, i_zf};

  //object creation: bvp stands for Boundary Value Problem
  telegraph bvp(endpoints, params, bcV, bcI, NT, NZ);

  bvp.setwV(); //solve for voltage
  //bvp.setwI(); //solve for current
  
  /*
  //print solution
  double vSol = 0.0, iSol = 0.0;
  std::cout << "Solution printing:" << std::endl;
  std::cout << "i  j | ti      zj     | wV(i,j) V(i,j) | |V-wV| |"
               " wI(i,j) I(i,j) | |I-wI| " << std::endl;
  
  for (unsigned int l = 0; l < 74; l++) std::cout << "-"; 
  std::cout << std::endl;
  
  for (unsigned int i = 0; i <= NT; i++)
  {
    for (unsigned int j = 0; j <= NZ; j++)
    {
      vSol = vSln(bvp.getT(i)/bvp.Jt, bvp.getZ(j)/bvp.Jz);
      iSol = iSln(bvp.getT(i)/bvp.Jt, bvp.getZ(j)/bvp.Jz);
      
      std::cout << printIndex << i << " " 
                << printIndex << j << "|"
                << printReal << bvp.getT(i)/bvp.Jt << " " 
                << printReal << bvp.getZ(j)/bvp.Jz << " |"
                << printReal << bvp.getwV(i, j) << " "
                << printReal << vSol << " |" 
                << printComp << fabs(vSol - bvp.getwV(i, j)) << "||"
                << printReal << bvp.getwI(i, j) << " "
                << printReal << iSol << " |" 
                << printComp << fabs(iSol - bvp.getwI(i, j)) << "|"
                << std::endl;
    }
  } //end printing
  */
  
  //write to files
  bvp.saveToFile("V", "Columns", "outputCols.dat");
  bvp.saveToFile("V", "Matrix", "outputMatrix.dat");

  return(0);
} //end main
