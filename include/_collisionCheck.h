#ifndef _COLLISIONCHECK_H
#define _COLLISIONCHECK_H

#include <_common.h>

class _collisionCheck
{
    public:
        _collisionCheck();
        virtual ~_collisionCheck();

        bool isLinearCol(vec3, vec3);
        bool isRadialCol(vec3, vec3,float,float,float);
        bool isPlaneCol(vec3, vec3);

    protected:

    private:
};

#endif // _COLLISIONCHECK_H
