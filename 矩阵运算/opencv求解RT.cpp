		cv::Mat PT1 = cv::Mat(5, 3, CV_64F, cv::Scalar(0));
		cv::Mat PT2 = cv::Mat(5, 3, CV_64F, cv::Scalar(0));
		cv::Mat CPT1 = cv::Mat(1, 3, CV_64F, cv::Scalar(0));
		cv::Mat CPT2 = cv::Mat(1, 3, CV_64F, cv::Scalar(0));
		cv::Mat S = cv::Mat(3, 1, CV_64F);
		cv::SVD thissvd;
		// 给点对矩阵赋值
		for (int v = 0; v < 5; v++)
		{
			for (int u = 0; u < 3; u++)
			{
				PT1.at<double>(v, u) = MaskRefe->at(v)[u];
				PT2.at<double>(v, u) = MaskFrom->at(v)[u];
			}
		}
		for (int u = 0; u < 3; u++)
		{
			double tmp1 = 0;
			double tmp2 = 0;
			for (int v = 0; v < 5; v++)
			{
				tmp1 += PT1.at<double>(v, u);
				tmp2 += PT2.at<double>(v, u);
			}
			CPT1.at<double>(0, u) = tmp1 * 0.2;
			CPT2.at<double>(0, u) = tmp2 * 0.2;
		}

		cv::Mat COV = cv::Mat(3, 3, CV_64F, cv::Scalar(0));
		for (int v = 0; v < 5; v++)
		{
			cv::Mat tmp1 = cv::Mat(1, 3, CV_64F, cv::Scalar(0));
			cv::Mat tmp2 = cv::Mat(1, 3, CV_64F, cv::Scalar(0));
			for (int u = 0; u < 3; u++)
			{
				tmp1.at<double>(0, u) = PT1.at<double>(v, u) - CPT1.at<double>(0, u);
				tmp2.at<double>(0, u) = PT2.at<double>(v, u) - CPT2.at<double>(0, u);
			}
			cv::Mat tmp1T = cv::Mat(3, 1, CV_64F, cv::Scalar(0));
			cv::transpose(tmp1, tmp1T);
			cv::Mat A = cv::Mat(3, 3, CV_64F, cv::Scalar(0));
			A = tmp1T * tmp2;
			COV = COV + A;
		}

		thissvd(COV, cv::SVD::FULL_UV);
		cv::Mat U = thissvd.u;
		cv::Mat VT = thissvd.vt;
		cv::Mat cvR = U * VT;
		cv::Mat E = cv::Mat(3, 3, CV_64F, cv::Scalar(0));
		E.at<double>(0, 0) = 1;
		E.at<double>(1, 1) = 1;
		E.at<double>(2, 2) = cv::determinant(cvR);
		cvR = U * E * VT;
		cv::Mat cvT = cv::Mat(3, 1, CV_64F, cv::Scalar(0));
		cv::Mat CPT1T = cv::Mat(3, 1, CV_64F, cv::Scalar(0));
		cv::Mat CPT2T = cv::Mat(3, 1, CV_64F, cv::Scalar(0));
		cv::transpose(CPT1, CPT1T);
		cv::transpose(CPT2, CPT2T);
		cvT = CPT1T - cvR * CPT2T;