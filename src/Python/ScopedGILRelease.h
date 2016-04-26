/*
 * ScopedGILRelease.h
 *
 *  Created on: 2016/04/24
 *      Author: tk
 */

#ifndef SRC_SCOPEDGILRELEASE_H_
#define SRC_SCOPEDGILRELEASE_H_
#include <boost/python.hpp>
class ScopedGILRelease
{
public:
   inline ScopedGILRelease()
   {
      d_gstate = PyGILState_Ensure();
   }

   inline ~ScopedGILRelease()
   {
      PyGILState_Release(d_gstate);
   }

private:
   PyGILState_STATE  d_gstate;
};

#endif /* SRC_SCOPEDGILRELEASE_H_ */
