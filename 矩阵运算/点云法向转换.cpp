dpt[0] = mR.el[0][0] * pVertex3d->norm.dX + mR.el[0][1] * pVertex3d->norm.dY + mR.el[0][2] * pVertex3d->norm.dZ;
dpt[1] = mR.el[1][0] * pVertex3d->norm.dX + mR.el[1][1] * pVertex3d->norm.dY + mR.el[1][2] * pVertex3d->norm.dZ;
dpt[2] = mR.el[2][0] * pVertex3d->norm.dX + mR.el[2][1] * pVertex3d->norm.dY + mR.el[2][2] * pVertex3d->norm.dZ;



// 点云法向变换
XW(0, 0) = ptCloud->pVertex[iCount].pt.dX;
XW(1, 0) = ptCloud->pVertex[iCount].pt.dY;
XW(2, 0) = ptCloud->pVertex[iCount].pt.dZ;
XC = mRWT * (XW - mTW);

double dNx, dNy, dNz;
dNx = mRWT(0, 0) * ptCloud->pVertex[iCount].norm.dX + mRWT(0, 1) * ptCloud->pVertex[iCount].norm.dY + mRWT(0, 2) * ptCloud->pVertex[iCount].norm.dZ;
dNy = mRWT(1, 0) * ptCloud->pVertex[iCount].norm.dX + mRWT(1, 1) * ptCloud->pVertex[iCount].norm.dY + mRWT(1, 2) * ptCloud->pVertex[iCount].norm.dZ;
dNz = mRWT(2, 0) * ptCloud->pVertex[iCount].norm.dX + mRWT(2, 1) * ptCloud->pVertex[iCount].norm.dY + mRWT(2, 2) * ptCloud->pVertex[iCount].norm.dZ;


XR = mRQX * (mRQ * XC + mTQ);

dNx = (mRQX * mRQ)(0, 0) * dNx + (mRQX * mRQ)(0, 1) * dNy + (mRQX * mRQ)(0, 2) * dNz;
dNy = (mRQX * mRQ)(1, 0) * dNx + (mRQX * mRQ)(1, 1) * dNy + (mRQX * mRQ)(1, 2) * dNz;
dNz = (mRQX * mRQ)(2, 0) * dNx + (mRQX * mRQ)(2, 1) * dNy + (mRQX * mRQ)(2, 2) * dNz;
                                
if (ptCloud->bLock)
    return -1;

ptCloud->pVertex[iCount].pt.dX = XR(0, 0);
ptCloud->pVertex[iCount].pt.dY = XR(1, 0);
ptCloud->pVertex[iCount].pt.dZ = XR(2, 0);
ptCloud->pVertex[iCount].norm.dX = dNx;
ptCloud->pVertex[iCount].norm.dY = dNy;
ptCloud->pVertex[iCount].norm.dZ = dNz;