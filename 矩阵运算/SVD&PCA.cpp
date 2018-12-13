/*
 * PCA主成分分析求解法向量, 全面最小二乘解
*/
void NormalsEstimation::pointSetPCA(const std::vector<Eigen::Vector3d>& pts, Eigen::Vector3d& normal)
{
	assert(pts.size() >= 3); //otherwise normals are undetermined
	Eigen::Map<const Eigen::Matrix3Xd> P(&pts[0].x(), 3, pts.size());

	Eigen::Vector3d centroid = P.rowwise().mean();
	Eigen::MatrixXd centered = P.colwise() - centroid;
	Eigen::Matrix3d cov = centered * centered.transpose();

	//eigvecs sorted in increasing order of eigvals
	//TODO: move out of function and reuse to increase speed 
	Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eig;//(cov);
	//eig.compute(cov);
	eig.computeDirect(cov); //https://eigen.tuxfamily.org/dox/classEigen_1_1SelfAdjointEigenSolver.html#afe520161701f5f585bcc4cedb8657bd1
	normal = eig.eigenvectors().col(0); //is already normalized
	if (normal(2) > 0)
	{
		normal = -normal; //flip towards camera, 从深度相机出来的点云定向一致
	}
}

/*
 * SVD求解法向量，全面最小二乘
*/
void NormalsEstimation::pointSetSVD(const std::vector<Eigen::Vector3d>& pts, Eigen::Vector3d& normal)
{
	assert(pts.size() >= 3); //otherwise normals are undetermined
	Eigen::Map<const Eigen::Matrix3Xd> P(&pts[0].x(), 3, pts.size());
	Eigen::Vector3d centroid = P.rowwise().mean();
	Eigen::MatrixXd centered = P.colwise() - centroid;
	Eigen::Matrix3d cov = centered * centered.transpose();

	Eigen::JacobiSVD<Eigen::MatrixXd> svd(cov, Eigen::ComputeFullV | Eigen::ComputeFullU); // ComputeThinU | ComputeThinV

	Eigen::MatrixXd singular_values = svd.singularValues();
	Eigen::MatrixXd left_singular_vectors = svd.matrixU();
	Eigen::MatrixXd right_singular_vectors = svd.matrixV();
	double nx = right_singular_vectors(0,2);
	double ny = right_singular_vectors(1,2);
	double nz = right_singular_vectors(2,2);
	double nn = nx * nx + ny * ny + nz * nz;
	nx = nx / sqrt(nn);
	ny = ny / sqrt(nn);
	nz = nz / sqrt(nn);
	normal.x() = nx;
	normal.y() = ny;
	normal.z() = nz;
	if (normal(2) > 0)
	{
		normal = -normal; //flip towards camera, 从深度相机出来的点云定向一致
	}
}