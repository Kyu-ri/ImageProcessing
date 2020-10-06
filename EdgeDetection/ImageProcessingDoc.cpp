
// ImageProcessingDoc.cpp : Implement a CImageProcessingDoc Class
//

#include "stdafx.h"
#include "ImageProcessing.h"

#include "DlgBrightnessOption.h"
#include "DlgMosaicOption.h"
#include "DlgCompositeOption.h"
#include "DlgIntensityTransformOption.h"
#include "DlgContrastStretchOption.h"

#include "ImageProcessingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
	ON_COMMAND(ID_PROCESS_MOSAIC, &CImageProcessingDoc::OnProcessMosaic)
	ON_COMMAND(ID_PROCESS_BRIGHTNESS, &CImageProcessingDoc::OnProcessBrightness)
	ON_COMMAND(ID_PROCESS_COMPOSITE, &CImageProcessingDoc::OnProcessComposite)
	ON_COMMAND(ID_PROCESS_INTENSITY_TRANSFORM, &CImageProcessingDoc::OnProcessIntensityTransform)
	ON_COMMAND(ID_PROCESS_CONTRAST_STRETCH, &CImageProcessingDoc::OnProcessContrastStretch)
	ON_COMMAND(ID_PROCESS_EQUALIZATION, &CImageProcessingDoc::OnProcessEqualization)
	ON_COMMAND(ID_32783, &CImageProcessingDoc::OnHistogramSpecification)
END_MESSAGE_MAP()


// CImageProcessingDoc Contruction/Destuction

CImageProcessingDoc::CImageProcessingDoc()
{
	//// TODO: Add an one-time generating code here
	m_pImage = NULL;
}

CImageProcessingDoc::~CImageProcessingDoc()
{
	if (NULL != m_pImage)
		delete m_pImage;
}

BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO: load imagefile // DONE
	m_pImage = new CxImage;
	m_pImage->Load(lpszPathName, FindType(lpszPathName));

	CalculateHistogram();

	return TRUE;
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//// TODO: Add a re-initialization code here
	//// SDI documents will reuse this article

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		//// TODO: Add a saving code here
	}
	else
	{
		//// TODO: Add a loading code here
	}
}


// CImageProcessingDoc diagnosis

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingDoc command

CString CImageProcessingDoc::FindExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(i+1);
		}
	}
	return CString(_T(""));
}

CString CImageProcessingDoc::RemoveExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(0,i);
		}
	}
	return name;
}

int CImageProcessingDoc::FindType(const CString& ext)
{
	return CxImage::GetTypeIdFromName(ext);
}

void CImageProcessingDoc::CalculateHistogram()
{
	// TODO: Add a calculating histogram code here
	if (m_pImage) {
		// Histogram function, which is implemented in Cximage
		 //m_histogramMax = m_pImage->Histogram(m_histogramRed, m_histogramGreen, m_histogramBlue, m_histogramGray);

		 
		// 가짜코드
		for (int i = 0; i < 256; i++){
			m_histogramRed[i]   = rand() % 200;
			m_histogramGreen[i] = rand() % 200;
			m_histogramBlue[i]  = rand() % 200;
			m_histogramGray[i]  = rand() % 200;
		}

		m_histogramMax = 0;
		for (int i = 0; i < 256; i++){
			m_histogramMax = max(m_histogramMax, m_histogramRed[i]  );
			m_histogramMax = max(m_histogramMax, m_histogramGreen[i]);
			m_histogramMax = max(m_histogramMax, m_histogramBlue[i] );
			m_histogramMax = max(m_histogramMax, m_histogramGray[i] );
		}
		//////////////////////////////////////////////////////////////
	}
}

void CImageProcessingDoc::OnProcessBrightness()
{
	// TODO: Add a changing the brightness histogram code here
	if (m_pImage) {
		DlgBrightnessOption dlg;

		if (dlg.DoModal() == IDOK) {
			// write your own code
			// for applying your effect, you must use m_pImage
			// this code is a simple example for manufacturing image : grayscaling

			int nPlusMinus = dlg.m_nPlusMinus;
			BYTE byModifyValue = dlg.m_byModifyValue;

			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();
			RGBQUAD color;
			RGBQUAD newcolor;

			for (DWORD y = 0; y < height; y++) {
				for (DWORD x = 0; x < width; x++) {
					color = m_pImage->GetPixelColor(x, y);
				
					if ((color.rgbRed + byModifyValue) >= 255) {
						color.rgbRed = (255 - byModifyValue);
					}
					if ((color.rgbGreen + byModifyValue) >= 255) {
						color.rgbGreen = (255 - byModifyValue);
					}
					if ((color.rgbBlue + byModifyValue) >= 255) {
						color.rgbBlue = (255 - byModifyValue);
					}

					if ((color.rgbRed - byModifyValue) < 0) {
						color.rgbRed = byModifyValue;
					}
					if ((color.rgbGreen - byModifyValue) < 0) {
						color.rgbGreen = byModifyValue;
					}
					if ((color.rgbBlue - byModifyValue) < 0) {
						color.rgbBlue = byModifyValue;
					}

					if (nPlusMinus == 0) {
						newcolor.rgbRed = (BYTE)(color.rgbRed + nPlusMinus + byModifyValue);
						newcolor.rgbGreen = (BYTE)(color.rgbGreen + nPlusMinus + byModifyValue);
						newcolor.rgbBlue = (BYTE)(color.rgbBlue + nPlusMinus + byModifyValue);
					}
					else{
						newcolor.rgbRed = (BYTE)(color.rgbRed + nPlusMinus -1 + byModifyValue*(-1));
						newcolor.rgbGreen = (BYTE)(color.rgbGreen + nPlusMinus -1 + byModifyValue * (-1));
						newcolor.rgbBlue = (BYTE)(color.rgbBlue + nPlusMinus - 1 + byModifyValue * (-1));
					}
					m_pImage->SetPixelColor(x, y, newcolor);
				}
			}

			// code to view overflow, Keep observation with the debugger
			BYTE a = 255;
			BYTE b = 1;
			int  c = 10;
			BYTE r;

			r = a + b;
			r = a + c;
			r = b + c;
		}
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnProcessMosaic()
{
	// TODO: Add a mosaic code here
	if (m_pImage) {
		DlgMosaicOption dlg;

		if (dlg.DoModal() == IDOK) {
			// write your own code
			// for applying your effect, you must use m_pImage
			// this code is a simple example for manufacturing image : grayscaling

			DWORD dwWindowSize = dlg.m_dwWindowSize;

			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();
			RGBQUAD color;
			RGBQUAD newcolor;

			

			int maskSize = dwWindowSize;
			int threshold = 100;

			CxImage* bufferG = new CxImage;
			bufferG->Create(width, height, 24, CXIMAGE_FORMAT_BMP);
			CxImage* bufferH = new CxImage;
			bufferH->Create(width, height, 24, CXIMAGE_FORMAT_BMP);
			CxImage* bufferV = new CxImage;
			bufferV->Create(width, height, 24, CXIMAGE_FORMAT_BMP);
			CxImage* bufferD1 = new CxImage;
			bufferD1->Create(width, height, 24, CXIMAGE_FORMAT_BMP);
			CxImage* bufferD2 = new CxImage;
			bufferD2->Create(width, height, 24, CXIMAGE_FORMAT_BMP);

			if (maskSize >= 0 && maskSize <= 4) {
				int maskH[3][3] = {
					{ -1, -2, -1 },
					{ 0, 0, 0 },
					{ 1, 2, 1 } };
				int maskV[3][3] = {
					{ -1, 0, 1 },
					{ -2, 0, 2 },
					{ -1, 0, 1 } };
				int maskD1[3][3] = {
					{ 0, 1, 2 },
					{ -1, 0, 1 },
					{ -2, -1, 0 } };
				int maskD2[3][3] = {
					{ -2, -1, 0 },
					{ -1, 0, 1 },
					{ 0, 1, 2 } };
				for (DWORD y = 0; y < height; y++) {
					for (DWORD x = 0; x < width; x++) {
						color = m_pImage->GetPixelColor(x, y);
						newcolor.rgbBlue = (BYTE)RGB2GRAY(color.rgbRed, color.rgbGreen, color.rgbBlue);
						newcolor.rgbGreen = (BYTE)RGB2GRAY(color.rgbRed, color.rgbGreen, color.rgbBlue);
						newcolor.rgbRed = (BYTE)RGB2GRAY(color.rgbRed, color.rgbGreen, color.rgbBlue);
						bufferG->SetPixelColor(x, y, newcolor);
						m_pImage->SetPixelColor(x, y, newcolor);
					}
				}

				int sumB = 0;
				int sumG = 0;
				int sumR = 0;
				for (DWORD y = 0; y < height - 2; y++) {
					for (DWORD x = 0; x < width - 2; x++) {
						sumB = 0;
						sumG = 0;
						sumR = 0;
						for (int i = 0; i < 3; i++) {
							for (int j = 0; j < 3; j++) {
								color = bufferG->GetPixelColor(x + i, y + j);
								sumB += color.rgbBlue * maskH[i][j];
								sumG += color.rgbGreen * maskH[i][j];
								sumR += color.rgbRed * maskH[i][j];
							}
						}
						if (sumB < 0) {
							sumB = -sumB;
						}
						if (sumG < 0) {
							sumG = -sumG;
						}
						if (sumR < 0) {
							sumR = -sumR;
						}
						if (sumB > 255) {
							sumB = 255;
						}
						if (sumG > 255) {
							sumG = 255;
						}
						if (sumR > 255) {
							sumR = 255;
						}
						newcolor.rgbBlue = sumB;
						newcolor.rgbGreen = sumG;
						newcolor.rgbRed = sumR;
						bufferH->SetPixelColor(x + 1, y + 1, newcolor);
					}
				}

				for (DWORD y = 0; y < height - 2; y++) {
					for (DWORD x = 0; x < width - 2; x++) {
						sumB = 0;
						sumG = 0;
						sumR = 0;
						for (int i = 0; i < 3; i++) {
							for (int j = 0; j < 3; j++) {
								color = bufferG->GetPixelColor(x + i, y + j);
								sumB += color.rgbBlue * maskV[i][j];
								sumG += color.rgbGreen * maskV[i][j];
								sumR += color.rgbRed * maskV[i][j];
							}
						}
						if (sumB < 0) {
							sumB = -sumB;
						}
						if (sumG < 0) {
							sumG = -sumG;
						}
						if (sumR < 0) {
							sumR = -sumR;
						}
						if (sumB > 255) {
							sumB = 255;
						}
						if (sumG > 255) {
							sumG = 255;
						}
						if (sumR > 255) {
							sumR = 255;
						}
						newcolor.rgbBlue = sumB;
						newcolor.rgbGreen = sumG;
						newcolor.rgbRed = sumR;
						bufferV->SetPixelColor(x + 1, y + 1, newcolor);
					}
				}
				for (DWORD y = 0; y < height - 2; y++) {
					for (DWORD x = 0; x < width - 2; x++) {
						sumB = 0;
						sumG = 0;
						sumR = 0;
						for (int i = 0; i < 3; i++) {
							for (int j = 0; j < 3; j++) {
								color = bufferG->GetPixelColor(x + i, y + j);
								sumB += color.rgbBlue * maskD1[i][j];
								sumG += color.rgbGreen * maskD1[i][j];
								sumR += color.rgbRed * maskD1[i][j];
							}
						}
						if (sumB < 0) {
							sumB = -sumB;
						}
						if (sumG < 0) {
							sumG = -sumG;
						}
						if (sumR < 0) {
							sumR = -sumR;
						}
						if (sumB > 255) {
							sumB = 255;
						}
						if (sumG > 255) {
							sumG = 255;
						}
						if (sumR > 255) {
							sumR = 255;
						}
						newcolor.rgbBlue = sumB;
						newcolor.rgbGreen = sumG;
						newcolor.rgbRed = sumR;
						bufferD1->SetPixelColor(x + 1, y + 1, newcolor);
					}
				}
				for (DWORD y = 0; y < height - 2; y++) {
					for (DWORD x = 0; x < width - 2; x++) {
						sumB = 0;
						sumG = 0;
						sumR = 0;
						for (int i = 0; i < 3; i++) {
							for (int j = 0; j < 3; j++) {
								color = bufferG->GetPixelColor(x + i, y + j);
								sumB += color.rgbBlue * maskD2[i][j];
								sumG += color.rgbGreen * maskD2[i][j];
								sumR += color.rgbRed * maskD2[i][j];
							}
						}
						if (sumB < 0) {
							sumB = -sumB;
						}
						if (sumG < 0) {
							sumG = -sumG;
						}
						if (sumR < 0) {
							sumR = -sumR;
						}
						if (sumB > 255) {
							sumB = 255;
						}
						if (sumG > 255) {
							sumG = 255;
						}
						if (sumR > 255) {
							sumR = 255;
						}
						newcolor.rgbBlue = sumB;
						newcolor.rgbGreen = sumG;
						newcolor.rgbRed = sumR;
						bufferD2->SetPixelColor(x + 1, y + 1, newcolor);
					}
				}
			}
			switch (maskSize) {
			case 0:
				for (DWORD y = 1; y < height - 1; y++) {
					for (DWORD x = 1; x < width - 1; x++) {
						newcolor = bufferH->GetPixelColor(x, y);
						if (RGB2GRAY(newcolor.rgbRed, newcolor.rgbGreen, newcolor.rgbBlue) > threshold) {
							newcolor.rgbBlue = 0;
							newcolor.rgbGreen = 0;
							newcolor.rgbRed = 255;
							m_pImage->SetPixelColor(x, y, newcolor);
						}
					}
				}
				for (DWORD y = 1; y < height - 1; y++) {
					for (DWORD x = 1; x < width - 1; x++) {
						newcolor = bufferV->GetPixelColor(x, y);
						if (RGB2GRAY(newcolor.rgbRed, newcolor.rgbGreen, newcolor.rgbBlue) > threshold) {
							newcolor.rgbBlue = 255;
							newcolor.rgbGreen = 0;
							newcolor.rgbRed = 0;
							m_pImage->SetPixelColor(x, y, newcolor);
						}
					}
				}
				for (DWORD y = 1; y < height - 1; y++) {
					for (DWORD x = 1; x < width - 1; x++) {
						newcolor = bufferD1->GetPixelColor(x, y);
						if (RGB2GRAY(newcolor.rgbRed, newcolor.rgbGreen, newcolor.rgbBlue) > threshold) {
							newcolor.rgbBlue = 0;
							newcolor.rgbGreen = 255;
							newcolor.rgbRed = 0;
							m_pImage->SetPixelColor(x, y, newcolor);
						}
					}
				}
				for (DWORD y = 1; y < height - 1; y++) {
					for (DWORD x = 1; x < width - 1; x++) {
						newcolor = bufferD2->GetPixelColor(x, y);
						if (RGB2GRAY(newcolor.rgbRed, newcolor.rgbGreen, newcolor.rgbBlue) > threshold) {
							newcolor.rgbBlue = 0;
							newcolor.rgbGreen = 255;
							newcolor.rgbRed = 255;
							m_pImage->SetPixelColor(x, y, newcolor);
						}
					}
				}

				break;
			case 1:
				for (DWORD y = 1; y < height - 1; y++) {
					for (DWORD x = 1; x < width - 1; x++) {
						newcolor = bufferH->GetPixelColor(x, y);
						if (RGB2GRAY(newcolor.rgbRed, newcolor.rgbGreen, newcolor.rgbBlue) > threshold) {
							newcolor.rgbBlue = 0;
							newcolor.rgbGreen = 0;
							newcolor.rgbRed = 255;
							m_pImage->SetPixelColor(x, y, newcolor);
						}
					}
				}
				break;
			case 2:
				for (DWORD y = 1; y < height - 1; y++) {
					for (DWORD x = 1; x < width - 1; x++) {
						newcolor = bufferV->GetPixelColor(x, y);
						if (RGB2GRAY(newcolor.rgbRed, newcolor.rgbGreen, newcolor.rgbBlue) > threshold) {
							newcolor.rgbBlue = 255;
							newcolor.rgbGreen = 0;
							newcolor.rgbRed = 0;
							m_pImage->SetPixelColor(x, y, newcolor);
						}
					}
				}
				break;
			case 3:
				for (DWORD y = 1; y < height - 1; y++) {
					for (DWORD x = 1; x < width - 1; x++) {
						newcolor = bufferD1->GetPixelColor(x, y);
						if (RGB2GRAY(newcolor.rgbRed, newcolor.rgbGreen, newcolor.rgbBlue) > threshold) {
							newcolor.rgbBlue = 0;
							newcolor.rgbGreen = 255;
							newcolor.rgbRed = 0;
							m_pImage->SetPixelColor(x, y, newcolor);
						}
					}
				}
				break;
			case 4:
				for (DWORD y = 1; y < height - 1; y++) {
					for (DWORD x = 1; x < width - 1; x++) {
						newcolor = bufferD2->GetPixelColor(x, y);
						if (RGB2GRAY(newcolor.rgbRed, newcolor.rgbGreen, newcolor.rgbBlue) > threshold) {
							newcolor.rgbBlue = 0;
							newcolor.rgbGreen = 255;
							newcolor.rgbRed = 255;
							m_pImage->SetPixelColor(x, y, newcolor);
						}
					}
				}
				break;

			default:
			{
				for (DWORD y = 0; y <= height / maskSize; y++) {
					for (DWORD x = 0; x <= width / maskSize; x++) {
						//color = m_pImage->GetPixelColor(x * 3, y * 3);
						int pixelNum = 0;
						int sumB = 0;
						int sumG = 0;
						int sumR = 0;
						for (int i = 0; i < maskSize && x * maskSize + i < width; i++) {
							for (int j = 0; j < maskSize && y * maskSize + j < height; j++) {
								color = m_pImage->GetPixelColor(x * maskSize + i, y * maskSize + j);
								sumB += color.rgbBlue;
								sumG += color.rgbGreen;
								sumR += color.rgbRed;
								pixelNum++;
							}
						}
						if (pixelNum == 0) {
							break;
						}
						sumB /= pixelNum;
						sumG /= pixelNum;
						sumR /= pixelNum;
						for (int i = 0; i < maskSize && x * maskSize + i < width; i++) {
							for (int j = 0; j < maskSize && y * maskSize + j < height; j++) {
								newcolor.rgbBlue = (BYTE)(sumB);
								newcolor.rgbGreen = (BYTE)(sumG);
								newcolor.rgbRed = (BYTE)(sumR);
								m_pImage->SetPixelColor(x * maskSize + i, y * maskSize + j, newcolor);
							}
						}

					}
				}
			}
			break;
			}
		}
	}
	CalculateHistogram();
	UpdateAllViews(NULL);
			/*
			for (DWORD setHeight = 0; setHeight < height; setHeight += dwWindowSize) {
				for (DWORD setWidth = 0; setWidth < width; setWidth += dwWindowSize) {

					DWORD sumOfSetBlue = 0;
					DWORD sumOfSetRed = 0;
					DWORD sumOfSetGreen = 0;

					for (DWORD y = setHeight; y < setHeight + dwWindowSize; y++) {
						for (DWORD x = setWidth; x < setWidth + dwWindowSize; x++) {
							color = m_pImage->GetPixelColor(x, y);

							sumOfSetBlue += color.rgbBlue;
							sumOfSetRed += color.rgbRed;
							sumOfSetGreen += color.rgbGreen;
						}
					}
					DWORD averOfSetBlue = sumOfSetBlue / (dwWindowSize * dwWindowSize);
					DWORD averOfSetRed = sumOfSetRed / (dwWindowSize * dwWindowSize);
					DWORD averOfSetGreen = sumOfSetGreen / (dwWindowSize * dwWindowSize);

					for (DWORD y = setHeight; y < setHeight + dwWindowSize; y++) {
						for (DWORD x = setWidth; x < setWidth + dwWindowSize; x++) {

							newcolor.rgbBlue = averOfSetBlue;
							newcolor.rgbRed = averOfSetRed;
							newcolor.rgbGreen = averOfSetGreen;

							m_pImage->SetPixelColor(x, y, newcolor);
						}
					}

					

				}
				*/


}

void CImageProcessingDoc::OnProcessComposite()
{
	// TODO: Add a composite code here
	if (m_pImage) {
		DlgCompositeOption dlg;

		if (dlg.DoModal() == IDOK) {
			int nOperatorID = dlg.GetCompositeOperatorID();
			CxImage * pSecondImage = dlg.GetSecondImage();

			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();
			RGBQUAD firstColor;
			RGBQUAD secondColor;
			RGBQUAD newColor;

			for (DWORD y = 0; y < height; y++) {
				for (DWORD x = 0; x < width; x++) {
					firstColor = m_pImage->GetPixelColor(x, y);
					secondColor = pSecondImage->GetPixelColor(x, y);

					if (nOperatorID == 0) {
						newColor.rgbBlue = (firstColor.rgbBlue + secondColor.rgbBlue);
						newColor.rgbGreen = (firstColor.rgbGreen + secondColor.rgbGreen);
						newColor.rgbRed = (firstColor.rgbRed + secondColor.rgbRed);
					}
					else {
						if ((firstColor.rgbBlue - secondColor.rgbBlue ) < 0) {
							secondColor.rgbBlue = 0;
						}
						if ((secondColor.rgbGreen - firstColor.rgbGreen) < 0) {
							secondColor.rgbGreen = 0;
						}
						if ((secondColor.rgbRed - firstColor.rgbRed) < 0) {
							secondColor.rgbRed = 0;
						}
						newColor.rgbBlue = (firstColor.rgbBlue - secondColor.rgbBlue);
						newColor.rgbGreen = (firstColor.rgbGreen - secondColor.rgbGreen);
						newColor.rgbRed = (firstColor.rgbRed - secondColor.rgbRed);
					}


					m_pImage->SetPixelColor(x, y, newColor);
				}
			}
		}
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnProcessIntensityTransform()
{
	// TODO: Add a Contrast conversion code here
	if (m_pImage) {
		DlgIntensityTransformOption dlg;

		if (dlg.DoModal() == IDOK) {
			int nTransformType = dlg.m_nTransformType;
			double nLinearTransfromCoefficient_a = dlg.m_nLinearTransfromCoefficient_a;
			double nLinearTransfromCoefficient_b = dlg.m_nLinearTransfromCoefficient_b;

			int byThresholdValue = dlg.m_byThresholdValue;

			BYTE byContrastStretching_Start = dlg.m_byContrastStretching_Start;
			BYTE byContrastStretching_End = dlg.m_byContrastStretching_End;

			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();
			RGBQUAD color;
			RGBQUAD newcolor;
		}
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnProcessContrastStretch()
{
	// TODO: Add a Contrast stretching code here
	if (m_pImage) {
		DlgContrastStretchOption dlg;

		if (dlg.DoModal() == IDOK) {
			int nStretchType = dlg.m_nStretchType;
			float fLow = dlg.m_fLow;
			float fHigh = dlg.m_fHigh;

			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();
			RGBQUAD color;
			RGBQUAD newcolor;

			BYTE LUT[256];

			// initialize thresholds
			int nLowTherhs = 0;
			int nHighThresh = 255;


			// compute thresholds
			if (nStretchType == 0) { // Auto

			} else if (nStretchType == 1) { // Ends-In

			}


			// compute LUT


			// trnasfer image
			for (DWORD y = 0; y < height; y++) {
				for (DWORD x = 0; x < width; x++) {
					color = m_pImage->GetPixelColor(x, y);

					// using LUT

					m_pImage->SetPixelColor(x, y, newcolor);
				}
			}
		}
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}

void CImageProcessingDoc::OnProcessEqualization()
{
	// TODO: Add a Histogram equalization code here
	if (m_pImage) 
	{

		DWORD width = m_pImage->GetWidth();
		DWORD height = m_pImage->GetHeight();
		RGBQUAD color;	// Save the current color value
		RGBQUAD newcolor;	// After the conversion, save the color value

		//(1) Histogram has already been generated histogram(Omission) 
		//(2) Create a cumulative histogram
		DWORD sum = 0;
		float scale_factor = 255.0 / (width*height);
		DWORD sum_hist[256]; // a cumulative histogram

		for(int i=0; i<256 ; i++)
		{
		// (Coding)

		}


		//(3) Calculating look-up table
		BYTE LUT[256]; // look-up table

		for(int i=0; i<256 ; i++)
		{
		// (Coding)  


		}

		// (4) Image Conversion
		for (DWORD y = 0; y < height; y++) 
		{
			for (DWORD x = 0; x < width; x++) 
			{
				color = m_pImage->GetPixelColor(x, y);
				// (Coding)



				m_pImage->SetPixelColor(x, y, newcolor);
			}
		}		
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}



void CImageProcessingDoc::OnHistogramSpecification()
{
	// TODO: Add a Histogram specifications code here
	if (m_pImage) 
	{

		DWORD width = m_pImage->GetWidth();
		DWORD height = m_pImage->GetHeight();
		RGBQUAD color;	// Save the current color value
		RGBQUAD newcolor;	// After the conversion, save the color value

		//(1) Histogram has already been generated histogram(Omission) 
		//(2) Create a cumulative histogram
		DWORD sum = 0;
		float scale_factor = 255.0 / (width*height);
		DWORD sum_hist[256]; // a cumulative histogram

		for(int i=0; i<256 ; i++)
		{
		// (coding)

		}


		//(3) Calculating look-up table
		BYTE LUT[256]; // look-up table

		for(int i=0; i<256 ; i++)
		{
		// (coding)  


		}


		// Same as histogram equalization code from here.
		// However, After a cumulative histogram convert to float sum_hist[256] and
		// modifing to be entered in the real number on calculating sum_hist


		//(4) 
		DWORD desired_histogram[256];
		// Making desired_histogram
/*
		//1.
		for (int i=0; i<=255; i++)
		{
			desired_histogram[i]=i;
		}
*/
/*
		//2.
		for (int i=0; i<=255; i++)
		{
			desired_histogram[i]=255-i;
		}
*/
/*
		//3.		
		for (int i=0; i<=127; i++)
		{
			desired_histogram[i]=127-i;
		}
		for (int i=128; i<=255; i++)
		{
			desired_histogram[i]=i-127;
		}
*/

		// redefinition
		sum = 0;
		scale_factor = 255.0 / (width*height);

		//(5) Create the cumulative histogram of histogram you want
		for(int i=0; i<256; i++)
		{
			//(coding)



		}

		//(6) Is the inverse.
		float difference;	// calculate the difference
		int min;	// Calculate the minimum of the difference
		DWORD inv_hist[256];	// reverse-histogram

		//(Hint) will use dual-route.
		// float fabs() Use library functions.
		for(int i=0; i<256; i++)
		{
		//(coding)




		}

		//(7) Create look-up table of reverse-histogram
		for(int i=0; i<256 ; i++)
		{
		//(coding)

		}
		
		

		// (8) Image Conversion
		for (DWORD y = 0; y < height; y++) 
		{
			for (DWORD x = 0; x < width; x++) 
			{
				color = m_pImage->GetPixelColor(x, y);
				// (coding)



				m_pImage->SetPixelColor(x, y, newcolor);
			}
		}		
	} // if(m_pImage)

	CalculateHistogram();
	UpdateAllViews(NULL);

	

}
