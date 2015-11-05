//
// <copyright file="CPUSparseMatrixTests.cpp" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//
#include "stdafx.h"
#include <crtdefs.h>
#include "..\..\..\Math\Math\CPUSparseMatrix.h"
#include <boost/test/unit_test.hpp>

using namespace Microsoft::MSR::CNTK;

namespace Microsoft
{
	namespace MSR
	{
		namespace CNTK
		{
			namespace Test
			{
				typedef CPUDoubleSparseMatrix SparseMatrix;
				typedef CPUDoubleMatrix DenseMatrix;

				BOOST_AUTO_TEST_SUITE(CPUSparseMatrixSuite)

					BOOST_AUTO_TEST_CASE(CPUSparseMatrixColumnSlice)
				{
					const size_t m = 100;
					const size_t n = 50;
					DenseMatrix dm0(m, n);
					SparseMatrix sm0(MatrixFormat::matrixFormatSparseCSC, m, n, 0);

					dm0.SetUniformRandomValue(-1, 1);

					foreach_coord(row, col, dm0)
					{
						sm0.SetValue(row, col, dm0(row, col));
					}

					const size_t start = 10;
					const size_t numCols = 20;
					DenseMatrix dm1 = dm0.ColumnSlice(start, numCols);
					DenseMatrix dm2 = sm0.ColumnSliceToDense(start, numCols);

					BOOST_CHECK(dm1.IsEqualTo(dm2, 0.0001));
				}

				BOOST_AUTO_TEST_SUITE_END()
			}
		}
	}
}