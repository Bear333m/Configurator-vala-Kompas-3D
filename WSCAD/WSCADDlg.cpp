
// WSCADDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "WSCAD.h"
#include "WSCADDlg.h"
#include "afxdialogex.h"
#include "math.h"
#include "C:\Program Files\ASCON\KOMPAS-3D v23 Study\SDK\Include\ksConstants.h"
#include "C:\Program Files\ASCON\KOMPAS-3D v23 Study\SDK\Include\ksConstants3D.h"
//#include "C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\Include\kapi5.h"
#include <atlsafe.h>
//#include <C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\Include\Ks_TLB.h>

#include <comutil.h>

#define PI 4*atan(1)


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma once


#import "C:\Program Files\ASCON\KOMPAS-3D v23 Study\SDK\lib\kAPI5.tlb"


using namespace Kompas6API5;
//using namespace KompasAPI5;


KompasObjectPtr pKompasApp5;
//KompasObjectPtr pKompasApp5;

ksPartPtr pPart;// = PartDoc->GetTopPart();
ksDocument3DPtr pDoc;


// диалоговое окно CWSCADDlg
CWSCADDlg::CWSCADDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_WSCAD_DIALOG, pParent)
	, m_dVhod(55)
	, m_lVhod(110)
	, m_dPodsh1(60)
	, m_lPodsh1(75)
	, m_dBurt(75)
	, m_lBurt(10.25)
	, m_dStup(65)
	, m_lStup(88)
	, m_dPodsh2(60)
	, m_lPodsh2(45)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWSCADDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_D_VHOD, m_dVhod);
	DDV_MinMaxDouble(pDX, m_dVhod, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_L_VHOD, m_lVhod);
	DDV_MinMaxInt(pDX, m_lVhod, 0, 10000);

	DDX_Text(pDX, IDC_EDIT_D_PODSH1, m_dPodsh1);
	DDV_MinMaxDouble(pDX, m_dPodsh1, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_L_PODSH1, m_lPodsh1);
	DDV_MinMaxDouble(pDX, m_lPodsh1, 0, 10000);

	DDX_Text(pDX, IDC_EDIT_D_BURT, m_dBurt);
	DDV_MinMaxDouble(pDX, m_dBurt, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_L_BURT, m_lBurt);
	DDV_MinMaxDouble(pDX, m_lBurt, 0, 10000);

	DDX_Text(pDX, IDC_EDIT_D_STUP, m_dStup);
	DDV_MinMaxDouble(pDX, m_dStup, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_L_STUP, m_lStup);
	DDV_MinMaxDouble(pDX, m_lStup, 0, 10000);

	DDX_Text(pDX, IDC_EDIT_D_PODSH2, m_dPodsh2);
	DDV_MinMaxDouble(pDX, m_dPodsh2, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_L_PODSH2, m_lPodsh2);
	DDV_MinMaxDouble(pDX, m_lPodsh2, 0, 10000);

	DDX_Control(pDX, IDC_RADIO_BURT_DO, m_radio_burt_do);
}

BEGIN_MESSAGE_MAP(CWSCADDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BUILD, &CWSCADDlg::OnBnClickedButtonBuild)
	ON_BN_CLICKED(IDOK, &CWSCADDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_BURT_DO, &CWSCADDlg::OnBnClickedRadioBurtDo)
	ON_BN_CLICKED(IDC_RADIO_BURT_POSLE, &CWSCADDlg::OnBnClickedRadioBurtPosle)
END_MESSAGE_MAP()


// обработчики сообщений CWSCADDlg

BOOL CWSCADDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	m_radio_burt_do.SetCheck(1);	// Устанавливаем, чтобы первый радиобаттон при создании окна был проставлен

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CWSCADDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CWSCADDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CWSCADDlg::CheckData()
{
	if (!UpdateData())
		return false;

	 return true;
}


void CWSCADDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	//if (pInvApp)
	//    pInvApp->MethodQuit();
	//   
	CDialog::OnOK();
}


//IKompasDocument3DPtr PartDoc;
void CWSCADDlg::OnBnClickedButtonBuild()
{
	// TODO: добавьте свой код обработчика уведомлений
	BeginWaitCursor();

	if (!CheckData())
		return;

	CComPtr<IUnknown> pKompasAppUnk = nullptr;
	if (!pKompasApp5)
	{
		// Получаем CLSID для Компас
		CLSID InvAppClsid;
		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) {
			pKompasApp5 = nullptr;
			return;
		}

		// Проверяем есть ли запущенный экземпляр Компас
		//если есть получаем IUnknown
		hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
		if (FAILED(hRes)) {
			// Приходится запускать Компас самим так как работающего нет
			// Также получаем IUnknown для только что запущенного приложения Компас
			TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
			hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
			if (FAILED(hRes)) {
				pKompasApp5 = nullptr;
				return;
			}
		}

		// Получаем интерфейс приложения Компас
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp5);
		if (FAILED(hRes)) {
			return;
		}
	}

	// делаем Компас видимым
	pKompasApp5->Visible = true;
	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pPart = pDoc->GetPart(pTop_Part);

	double current_length = 0;
	double lShponk[35] = { 6, 8, 10, 12,
		14, 16, 18, 20, 22, 25, 28, 32, 36, 40, 45, 50, 56, 63, 70, 80, 90, 100,
		110, 125, 140, 160, 180, 200, 220, 250, 280, 320, 400, 450, 500 };		//ГОСТ 23360-78
	double sizesShponk[13][4] = {		//мин д вала, макс д вала, ширина паза, глубина паза
		{10, 12, 4, 2},
		{12, 17, 5, 3},
		{17, 22, 6, 4},
		{22, 30, 8, 4},
		{30, 38, 10, 5},
		{38, 44, 12, 5},
		{44, 50, 14, 6},
		{50, 58, 16, 6},
		{58, 65, 18, 7},
		{65, 75, 20, 8},
		{75, 85, 22, 9},
		{85, 95, 25, 9},
		{95, 110, 28, 10}
	};

	ksSketchDefinitionPtr pSketchDef;
	ksDocument2DPtr p2DDoc;
	ksBossExtrusionDefinitionPtr pExDef;
	ksCutExtrusionDefinitionPtr pExDefCut;
	ksPlaneOffsetDefinitionPtr pPlaneDef;
	ksChamferDefinitionPtr filletDef;


	// ВХОДНАЯ СТУПЕНЬ
	ksEntityPtr pSketchVhod = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketchVhod->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
	pSketchVhod->Create();

	p2DDoc = pSketchDef->BeginEdit();
	p2DDoc->ksCircle(0, 0, m_dVhod / 2.f, 1);		//у меня переменная диаметра, а аргумент радиуса
	pSketchDef->EndEdit();

	ksEntityPtr pExtrudeVhod = pPart->NewEntity(o3d_bossExtrusion);	//приклеивание выдавливанимем
	pExDef = pExtrudeVhod->GetDefinition();
	pExDef->directionType = dtNormal;
	pExDef->SetSketch(pSketchVhod);
	pExDef->SetSideParam(true, etBlind, m_lVhod, 0, false);		//side1 это направление выдавливания
	pExtrudeVhod->Create();

	//ШПОНКА НА ВХОДНОЙ СТУПЕНИ
	int num_l = GetShponkLength(m_lVhod, lShponk);
	int num_s = GetShponkSizes(m_dVhod, sizesShponk);
	double otstup = (m_lVhod - lShponk[num_l]) / 2;
	double center1 = otstup + sizesShponk[num_s][2] / 2;		//расстояние до начала дуги +  расстояние до начала прямой
	double center2 = m_lVhod - otstup - sizesShponk[num_s][2] / 2;
	double shir = sizesShponk[num_s][2] / 2;					//расстояние от центра до края

	ksEntityPtr pPlaneShponk1 = pPart->NewEntity(o3d_planeOffset);			//объявил смещённую плоскость конкретную
	pPlaneDef = pPlaneShponk1->GetDefinition();
	pPlaneDef->direction = true;
	pPlaneDef->offset = m_dVhod / 2;
	pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));
	pPlaneShponk1->Create();

	ksEntityPtr pSketchShponk1 = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketchShponk1->GetDefinition();
	pSketchDef->SetPlane(pPlaneShponk1);
	pSketchShponk1->Create();

	p2DDoc = pSketchDef->BeginEdit();
	p2DDoc->ksArcByPoint(0, -center1, shir, shir, -center1, -shir, -center1, true, 1);	//то, будет построенна дуга большая или маленькая, зависит от порядка точек границ дуги
	p2DDoc->ksArcByPoint(0, -center2, shir, -shir, -center2, shir, -center2, true, 1);
	p2DDoc->ksLineSeg(shir, -center1, shir, -center2, 1);
	p2DDoc->ksLineSeg(-shir, -center1, -shir, -center2, 1);
	pSketchDef->EndEdit();

	ksEntityPtr pCutShponk1 = pPart->NewEntity(o3d_cutExtrusion);
	pExDefCut = pCutShponk1->GetDefinition();		//создаём объект вырезания
	pExDefCut->directionType = dtNormal;
	pExDefCut->SetSketch(pSketchShponk1);
	pExDefCut->SetSideParam(true, etBlind, sizesShponk[num_s][3], 0, false);		//side1 это направление выдавливания
	pCutShponk1->Create();

	current_length += m_lVhod;


	//ЛЕВАЯ СТУПЕНЬ ПОД ПОДШИПНИКОМ
	ksEntityPtr pPlanePodsh1 = pPart->NewEntity(o3d_planeOffset);			//объявил смещённую плоскость конкретную
	pPlaneDef = pPlanePodsh1->GetDefinition();
	pPlaneDef->direction = true;
	pPlaneDef->offset = current_length;
	pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
	pPlanePodsh1->Create();

	ksEntityPtr pSketchPodsh1 = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketchPodsh1->GetDefinition();
	pSketchDef->SetPlane(pPlanePodsh1);
	pSketchPodsh1->Create();

	p2DDoc = pSketchDef->BeginEdit();
	p2DDoc->ksCircle(0, 0, m_dPodsh1 / 2.f, 1);		//у меня переменная диаметра, а аргумент радиуса
	pSketchDef->EndEdit();

	ksEntityPtr pExtrudePodsh1 = pPart->NewEntity(o3d_bossExtrusion);	//приклеивание выдавливанимем
	pExDef = pExtrudePodsh1->GetDefinition();
	pExDef->directionType = dtNormal;
	pExDef->SetSketch(pSketchPodsh1);
	pExDef->SetSideParam(true, etBlind, m_lPodsh1, 0, false);		//side1 это направление выдавливания
	pExtrudePodsh1->Create();

	current_length += m_lPodsh1;


	//ЛЕВЫЙ УПОРНЫЙ БОРТИК
	if (mode_burt == 0) {
		ksEntityPtr pPlaneBurt = pPart->NewEntity(o3d_planeOffset);			//объявил смещённую плоскость конкретную
		pPlaneDef = pPlaneBurt->GetDefinition();
		pPlaneDef->direction = true;
		pPlaneDef->offset = current_length;
		pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
		pPlaneBurt->Create();

		ksEntityPtr pSketchBurt = pPart->NewEntity(o3d_sketch);
		pSketchDef = pSketchBurt->GetDefinition();
		pSketchDef->SetPlane(pPlaneBurt);
		pSketchBurt->Create();

		p2DDoc = pSketchDef->BeginEdit();
		p2DDoc->ksCircle(0, 0, m_dBurt / 2.f, 1);		//у меня переменная диаметра, а аргумент радиуса
		pSketchDef->EndEdit();

		ksEntityPtr pExtrudeBurt = pPart->NewEntity(o3d_bossExtrusion);	//приклеивание выдавливанимем
		pExDef = pExtrudeBurt->GetDefinition();
		pExDef->directionType = dtNormal;
		pExDef->SetSketch(pSketchBurt);
		pExDef->SetSideParam(true, etBlind, m_lBurt, 0, false);		//side1 это направление выдавливания
		pExtrudeBurt->Create();

		current_length += m_lBurt;
	}


	//СТУПИЦА
	ksEntityPtr pPlaneStup = pPart->NewEntity(o3d_planeOffset);			//объявил смещённую плоскость конкретную
	pPlaneDef = pPlaneStup->GetDefinition();	//объявил смещённую плоскость общую
	pPlaneDef->direction = true;
	pPlaneDef->offset = current_length;
	pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
	pPlaneStup->Create();

	ksEntityPtr pSketchStup = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketchStup->GetDefinition();
	pSketchDef->SetPlane(pPlaneStup);
	pSketchStup->Create();

	p2DDoc = pSketchDef->BeginEdit();
	p2DDoc->ksCircle(0, 0, m_dStup / 2.f, 1);		//у меня переменная диаметра, а аргумент радиуса
	pSketchDef->EndEdit();

	ksEntityPtr pExtrudeStup = pPart->NewEntity(o3d_bossExtrusion);	//приклеивание выдавливанимем
	pExDef = pExtrudeStup->GetDefinition();
	pExDef->directionType = dtNormal;
	pExDef->SetSketch(pSketchStup);
	pExDef->SetSideParam(true, etBlind, m_lStup, 0, false);		//side1 это направление выдавливания
	pExtrudeStup->Create();

	//ШПОНКА НА СТУПИЦЕ
	num_l = GetShponkLength(m_lStup, lShponk);
	num_s = GetShponkSizes(m_dStup, sizesShponk);
	otstup = (m_lStup - lShponk[num_l]) / 2;
	center1 = current_length + otstup + sizesShponk[num_s][2] / 2;		//расстояние до начала дуги +  расстояние до начала прямой
	center2 = current_length + m_lStup - otstup - sizesShponk[num_s][2] / 2;
	shir = sizesShponk[num_s][2] / 2;									//расстояние от центра до края

	ksEntityPtr pPlaneShponk2 = pPart->NewEntity(o3d_planeOffset);			//объявил смещённую плоскость конкретную
	pPlaneDef = pPlaneShponk2->GetDefinition();
	pPlaneDef->direction = true;
	pPlaneDef->offset = m_dStup / 2;
	pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));
	pPlaneShponk2->Create();

	ksEntityPtr pSketchShponk2 = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketchShponk2->GetDefinition();
	pSketchDef->SetPlane(pPlaneShponk2);
	pSketchShponk2->Create();

	p2DDoc = pSketchDef->BeginEdit();
	p2DDoc->ksArcByPoint(0, -center1, shir, shir, -center1, -shir, -center1, true, 1);	//то, будет построенна дуга большая или маленькая, зависит от порядка точек границ дуги
	p2DDoc->ksArcByPoint(0, -center2, shir, -shir, -center2, shir, -center2, true, 1);
	p2DDoc->ksLineSeg(shir, -center1, shir, -center2, 1);
	p2DDoc->ksLineSeg(-shir, -center1, -shir, -center2, 1);
	pSketchDef->EndEdit();

	ksEntityPtr pCutShponk2 = pPart->NewEntity(o3d_cutExtrusion);
	pExDefCut = pCutShponk2->GetDefinition();		//создаём объект вырезания
	pExDefCut->directionType = dtNormal;
	pExDefCut->SetSketch(pSketchShponk2);
	pExDefCut->SetSideParam(true, etBlind, sizesShponk[num_s][3], 0, false);		//side1 это направление выдавливания
	pCutShponk2->Create();

	current_length += m_lStup;


	//ПРАВЫЙ УПОРНЫЙ БОРТИК
	if (mode_burt == 1) {
		ksEntityPtr pPlaneBurt = pPart->NewEntity(o3d_planeOffset);			//объявил смещённую плоскость конкретную
		pPlaneDef = pPlaneBurt->GetDefinition();
		pPlaneDef->direction = true;
		pPlaneDef->offset = current_length;
		pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
		pPlaneBurt->Create();

		ksEntityPtr pSketchBurt = pPart->NewEntity(o3d_sketch);
		pSketchDef = pSketchBurt->GetDefinition();
		pSketchDef->SetPlane(pPlaneBurt);
		pSketchBurt->Create();

		p2DDoc = pSketchDef->BeginEdit();
		p2DDoc->ksCircle(0, 0, m_dBurt / 2.f, 1);		//у меня переменная диаметра, а аргумент радиуса
		pSketchDef->EndEdit();

		ksEntityPtr pExtrudeBurt = pPart->NewEntity(o3d_bossExtrusion);	//приклеивание выдавливанимем
		pExDef = pExtrudeBurt->GetDefinition();
		pExDef->directionType = dtNormal;
		pExDef->SetSketch(pSketchBurt);
		pExDef->SetSideParam(true, etBlind, m_lBurt, 0, false);		//side1 это направление выдавливания
		pExtrudeBurt->Create();

		current_length += m_lBurt;
	}

	//ПРАВАЯ СТУПЕНЬ ПОД ПОДШИПНИКОМ
	ksEntityPtr pPlanePodsh2 = pPart->NewEntity(o3d_planeOffset);			//объявил смещённую плоскость конкретную
	pPlaneDef = pPlanePodsh2->GetDefinition();
	pPlaneDef->direction = true;
	pPlaneDef->offset = current_length;
	pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
	pPlanePodsh2->Create();

	ksEntityPtr pSketchPodsh2 = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketchPodsh2->GetDefinition();
	pSketchDef->SetPlane(pPlanePodsh2);
	pSketchPodsh2->Create();

	p2DDoc = pSketchDef->BeginEdit();
	p2DDoc->ksCircle(0, 0, m_dPodsh2 / 2.f, 1);		//у меня переменная диаметра, а аргумент радиуса
	pSketchDef->EndEdit();

	ksEntityPtr pExtrudePodsh2 = pPart->NewEntity(o3d_bossExtrusion);	//приклеивание выдавливанимем
	pExDef = pExtrudePodsh2->GetDefinition();
	pExDef->directionType = dtNormal;
	pExDef->SetSketch(pSketchPodsh2);
	pExDef->SetSideParam(true, etBlind, m_lPodsh2, 0, false);		//side1 это направление выдавливания
	pExtrudePodsh2->Create();

	current_length += m_lPodsh2;


	//ФАСКА
	ksEntityPtr filletEntity = pPart->NewEntity(o3d_chamfer);
	filletDef = filletEntity->GetDefinition();

	filletDef->SetChamferParam(TRUE, 2, 2);
	ksEntityCollectionPtr EdgeCollection = filletDef->array();		//создаём массив рёбер
	EdgeCollection->Clear();

	ksEntityCollectionPtr edges = pPart->EntityCollection(o3d_edge);
	edges->SelectByPoint(0, 0, m_dVhod / 2);
	EdgeCollection->Add(edges->GetByIndex(0));
	edges = pPart->EntityCollection(o3d_edge);
	edges->SelectByPoint(0, current_length, m_dPodsh2 / 2);
	EdgeCollection->Add(edges->GetByIndex(0));

	filletEntity->Create();

	pDoc->SaveAs("D:\\Projects\\Детмаш\\Программа\\Detail.m3d");
}



void CWSCADDlg::OnBnClickedRadioBurtDo()
{
	mode_burt = 0;
}

void CWSCADDlg::OnBnClickedRadioBurtPosle()
{
	mode_burt = 1;
}

int CWSCADDlg::GetShponkLength(double length, double lShponk[35])
{
	for (int i = 2; i <= 50; i++) {
		double shponk_length = length - i;
		for (int j = 34; j >= 0; j--) {
			if (lShponk[j] == shponk_length) return j;
		}
	}
	return 0;
}

int CWSCADDlg::GetShponkSizes(double d, double sizesShponk[13][4]) {
	for (int i = 0; i <= 13; i++) {
		if (sizesShponk[i][0] < d && d <= sizesShponk[i][1]) return i;
	}
	return 0;
}
