#include <test.h>
#include <test_space.h>
#include <test_manager.h>
#include <test_service.h>
#include <test_draw.h>
#include <test_window.h>
#include <test_samples.h>
#include <surf_cover_surface.h>
#include <cur_arc3d.h>
#include <vector>
#include <alg_curve_fillet.h>
using namespace std;
using namespace c3d;
using namespace TestVariables;
#include <surf_corner_surface.h>
#include <cur_bezier3d.h>
#include <cur_line_segment3d.h>
#include <cur_arc3d.h>

#include <action_point.h>
#include <action_curve.h>
#include <action_curve3d.h>
#include <action_surface_curve.h>
#include <action_surface.h>
#include <action_direct.h>
#include <action_mesh.h>
#include <action_phantom.h>
#include <action_shell.h>
#include <action_sheet.h>
#include <action_solid.h>

#include <templ_s_array.h>
#include <templ_rp_array.h>
#include <templ_array2.h>
#include <templ_sptr.h>
#include <templ_dptr.h>

#include <mb_cart_point.h>
#include <mb_cart_point3d.h>
#include <mb_matrix.h>
#include <mb_matrix3d.h>
#include <mb_matrixnn.h>
#include <mb_placement.h>
#include <mb_placement3d.h>
#include <mb_axis3d.h>
#include <mb_thread.h>
#include <mb_nurbs_function.h>

#include <function.h>
#include <function_factory.h>

#include <curve.h>
#include <cur_line_segment.h>
#include <cur_arc.h>
#include <cur_nurbs.h>
#include <cur_polyline.h>
#include <cur_character_curve.h>
#include <cur_projection_curve.h>
#include <cur_reparam_curve.h>
#include <cur_trimmed_curve.h>
#include <cur_contour.h>

#include <region.h>
#include <contour_graph.h>

#include <curve3d.h>
#include <cur_line_segment3d.h>
#include <cur_arc3d.h>
#include <cur_nurbs3d.h>
#include <cur_plane_curve.h>
#include <cur_surface_curve.h>
#include <cur_contour_on_surface.h>
#include <cur_surface_intersection.h>
#include <cur_spiral.h>
#include <cur_character_curve3d.h>
#include <cur_reparam_curve3d.h>
#include <cur_trimmed_curve3d.h>
#include <cur_contour3d.h>

#include <surface.h>
#include <surf_plane.h>
#include <surf_cylinder_surface.h>
#include <surf_cone_surface.h>
#include <surf_sphere_surface.h>
#include <surf_torus_surface.h>
#include <surf_extrusion_surface.h>
#include <surf_revolution_surface.h>
#include <surf_lofted_surface.h>
#include <surf_evolution_surface.h>
#include <surf_spiral_surface.h>
#include <surf_spline_surface.h>
#include <surf_offset_surface.h>
#include <surf_curve_bounded_surface.h>

#include <attribute.h>
#include <attr_color.h>
#include <attr_dencity.h>
#include <attr_identifier.h>
#include <attr_selected.h>
#include <attr_user_attribut.h>

#include <name_item.h>
#include <name_check.h>

#include <topology.h>
#include <topology_faceset.h>
#include <check_geometry.h>

#include <point3d.h>
#include <point_frame.h>
#include <wire_frame.h>
#include <creator.h>
#include <solid.h>
#include <instance.h>
#include <plane_instance.h>
#include <space_instance.h>
#include <assembly.h>

#include <mesh.h>
#include <mesh_grid.h>
#include <mesh_primitive.h>
#include <mesh_polygon.h>

#include <map_create.h>
#include <map_lump.h>
#include <map_section.h>
#include <map_section_complex.h>       
#include <map_thread.h>

#include <tri_face.h>

#include <mip_curve_properties.h>
#include <mip_solid_area_volume.h>
#include <mip_solid_mass_inertia.h>

#include <alg_base.h>
#include <alg_draw.h>

#include <generic_utility.h>

#include <algorithm>
#include <ctime>
#include <functional>
#include <map>
#include <vector>
#include <utility>

#include "cur_polyline3d.h"
#include "cur_arc3d.h"
#include "action_solid.h"

#include <math_namespace.h>
#include <last.h>
#include <cur_cone_spiral.h>
#include <surf_mesh_surface.h>


//Гайка
void CreateSketch2(RPArray<MbContour>& _arrContours)
{
    // Центры и радиусы окружностей, дуги которых входят в контур 
    const MbCartPoint centerCircle(0, 0);
    const double RAD = 20;
    // Количество сторон многоугольника
    const int SIDE_CNT = 6;
    // Радиус описывающей окружности многоугольника
    const double RAD1 = 45.0;

    // Массив для хранения вершин ломаной 
    SArray<MbCartPoint> arrPnts(SIDE_CNT);
    // Вычисление вершин ломаной равномерным делением окружности
    for (int i = 0; i < SIDE_CNT; i++)
    {
        // Угловое положение i-й вершины на описывающей окружности.
        // Угловое положение начальной вершины - M_PI/2 (эта вершина 
        // расположена на вертикальной оси).
        double angle = M_PI / 2 + 2 * M_PI / SIDE_CNT * i;
        MbCartPoint pnt(RAD1 * cos(angle), RAD1 * sin(angle));
        arrPnts.Add(pnt);
    }

    // Построение единой ломаной внешнего контура по точкам 
    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContour = new MbContour(*pPolyline, true);

    MbArc* pCircle = new MbArc(centerCircle, RAD);
    MbContour* pContourCircle = new MbContour(*pCircle, true);
    _arrContours.push_back(pContour);
    _arrContours.push_back(pContourCircle);
}
void CreateSketch01(RPArray<MbContour>& _arrContours)
{
    double R = 18;
    double l = 2;
    SArray<MbCartPoint>arrPnts(4);
    arrPnts.Add(MbCartPoint(-l * 0.1 + l, -l + R));
    arrPnts.Add(MbCartPoint(l * 0.1 + l, -l + R));
    arrPnts.Add(MbCartPoint(2*l, l + R));
    arrPnts.Add(MbCartPoint(0, l + R));

    MbLineSegment* pS1 = new MbLineSegment(arrPnts[0], arrPnts[1]);
    MbContour* pContour = new MbContour(*pS1, true);

    MbLineSegment* pS2 = new MbLineSegment(arrPnts[1], arrPnts[2]);
    pContour->AddSegment(pS2);

    MbLineSegment* pS3 = new MbLineSegment(arrPnts[2], arrPnts[3]);
    pContour->AddSegment(pS3);

    MbLineSegment* pS4 = new MbLineSegment(arrPnts[3], arrPnts[0]);
    pContour->AddSegment(pS4);

    _arrContours.push_back(pContour);
}
void MakeUserCommand0()
{
    MbPlacement3D pl; // Локальная СК (по умолчанию совпадает с мировой СК) 
    // СОЗДАНИЕ КОНТУРОВ ДЛЯ ОБРАЗУЮЩЕЙ 
    RPArray<MbContour> arrContours;
    CreateSketch2(arrContours);

    // Отображение образующей (в плоскости XY глобальной СК) 
    for (int i = 0; i < arrContours.size(); i++)
        viewManager->AddObject(Style(1, RGB(0, 0, 255)), arrContours[i], &pl);

    // ПОСТРОЕНИЕ ТЕЛА ВЫДАВЛИВАНИЯ 
    // Образующая размещается на плоскости XY глобальной СК. 
    // Важное замечание: объект-плоскость должен создаваться динамически, 
    // поскольку он продолжает использоваться в объекте-твердом теле после 
    // выхода из данной функции. 
    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 1, 0));

    // Объект, хранящий параметры образующей 
    MbSweptData sweptData(*pPlaneXY, arrContours);

    // Направляющий вектор для операции выдавливания 
    MbVector3D dir(0, 0, -1);

    // Параметры операции выдавливания, задающие свойства тела для построения: 
    // расстояние выдавливания в прямом и в обратном направлении вдоль 
    // направляющего вектора 
    const double HEIGHT_FORWARD = 30.0, HEIGHT_BACKWARD = 0.0;
    ExtrusionValues extrusionParam(HEIGHT_FORWARD, HEIGHT_BACKWARD);

    // Служебный объект для именования элементов модели твердого тела 
    MbSNameMaker operNames(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    // Построение твердого тела выдавливания 
    MbSolid* pSolid = NULL;
    MbResultType res = ::ExtrusionSolid(sweptData, dir, NULL, NULL, false,
        extrusionParam, operNames, cNames, pSolid);

    // Локальная СК (по умолчанию совпадает с мировой СК)
    MbPlacement3D pl1;
    // Построение направляющей кривой в виде незамкнутого NURBS-сплайна
    // 4-го порядка по контрольным точкам
    MbConeSpiral* pSpiral = new MbConeSpiral(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, -26),
        MbCartPoint3D(0, 26, 0), 4, false);

    // Описание образующей кривой в виде плоского контура на плоскости XY мировой СК
    MbPlane* pPlaneXY1 = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, -50),
        MbCartPoint3D(0, 50, 0));
    // Построение образующей кривой с помощью вспомогательной функции CreateSketch

    RPArray<MbContour> arrContours1;
    CreateSketch01(arrContours1);
    MbSweptData sweptData1(*pPlaneXY1, arrContours1);

    // Объект с параметрами операции построения тела заметания
    EvolutionValues params;
    // Вариант плоскопараллельного движения образующей вдоль направляющей
    params.parallel = 1;
    // Служебные объекты-именователи для вызова геометрической операции
    MbSNameMaker operNames1(ct_CurveEvolutionSolid, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker cNames1(ct_CurveSweptSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> contourNames(1, 0, false);
    contourNames.Add(&cNames1);
    MbSNameMaker splineNames(ct_CurveSweptSolid, MbSNameMaker::i_SideNone, 0);
    // Вызов операции построения тела заметания
    MbSolid* pSolid1 = NULL;
    MbResultType res1 = ::EvolutionSolid(sweptData1, *pSpiral, params, operNames1,
        contourNames, splineNames, pSolid1);
    // Отображение построенного тела
    viewManager->AddObject(Style(1, LIGHTGRAY), pSolid1);
    if (res1 == rt_Success)
        viewManager->AddObject(Style(1, LIGHTGRAY), pSolid1);

    // Отображение построенного тела 
    if (res == rt_Success)
    {
        viewManager->AddObject(Style(1, LIGHTGRAY), pSolid);
    }

    // Уменьшение счетчиков ссылок динамически созданных объектов ядра 
    ::DeleteItem(pSolid);
    ::DeleteItem(pPlaneXY);
    for (int i = 0; i < arrContours.size(); i++)
    ::DeleteItem(arrContours[i]);

    ::DeleteItem(pSolid1);
    ::DeleteItem(pPlaneXY1);
    ::DeleteItem(pSpiral);
}

/////////////////////////////////////////////////////////////////////////////////

void MakeUserCommand1()
{
    // Базовая поверхность вращения: построение по образующей, оси вращения и углу
    SArray<MbCartPoint3D> arrGenPnts(7);
    arrGenPnts.Add(MbCartPoint3D(2.5, 20, 0));
    arrGenPnts.Add(MbCartPoint3D(4, 10, 0));
    arrGenPnts.Add(MbCartPoint3D(9.7, 7.4, 0));
    arrGenPnts.Add(MbCartPoint3D(9.7, 4, 0));
    arrGenPnts.Add(MbCartPoint3D(7.6, 2.2, 0));
    arrGenPnts.Add(MbCartPoint3D(10, -7, 0));
    arrGenPnts.Add(MbCartPoint3D(9.8, -11, 0));
    MbBezier3D* pGenCurve = new MbBezier3D(arrGenPnts, false);
    MbAxis3D axRev(MbCartPoint3D(0, 0, 0), MbVector3D(0, 1, 0));
    MbRevolutionSurface* pBaseSurf = new MbRevolutionSurface(
        *pGenCurve, axRev, 2 * M_PI, false);

    // Построение эквидистантной поверхности 
    MbOffsetSurface* pOffSurf = new MbOffsetSurface(*pBaseSurf, 5, false);
    // Смещение pOffSurf вдоль оси X для удобства отображения
    pOffSurf->Move(MbVector3D(45, 0, 0));

    // Отображение поверхностей
    viewManager->AddObject(Style(1, GREEN), pBaseSurf);
    viewManager->AddObject(Style(1, LIGHTGRAY), pOffSurf);

    // Уменьшение счетчика ссылок динамически созданных объектов ядра
    ::DeleteItem(pGenCurve);
    ::DeleteItem(pBaseSurf);
    ::DeleteItem(pOffSurf);

}

/////////////////////////////////////////////////////////////////////////////////

//сеточная поверхность (Лист изогнутый)
void MakeUserCommand2()
{
    // Первое семейство координатных кривых: 
//   - кривые Безье, представляющие два периода синусоиды (растянутые 
//     на отрезок U_SIN_DX).
//   - U_CURVES_CNT кривых расположены вдоль оси Z на равных промежутках 
//     в интервале шириной U_DZ
    const int    U_CURVES_CNT = 10;
    const double U_DZ = 30;
    const int    U_SIN_PERIOD_CNT = 2;
    const double U_SIN_DX = 15;
    const int    U_BEZIER_PNT_CNT = 15;
    RPArray<MbCurve3D> arrCurvesU;
    for (int i = 0; i < U_CURVES_CNT; i++)
    {
        SArray<MbCartPoint3D> arrPnts;
        for (int n = 0; n < U_BEZIER_PNT_CNT; n++)
        {
            MbCartPoint3D p;
            p.x = n * U_SIN_DX / (U_BEZIER_PNT_CNT - 1);
            p.y = sin(p.x / U_SIN_DX * 2 * M_PI * U_SIN_PERIOD_CNT);
            p.z = i * U_DZ / (U_CURVES_CNT - 1);
            arrPnts.push_back(p);
        }
        MbBezier3D* pc = new MbBezier3D(arrPnts, false);
        arrCurvesU.Add(pc);
    }

    // Второе семейство координатных кривых: 
    //   - кривые Безье, представляющие три периода синусоиды (растянутые 
    //     на отрезок V_SIN_DZ).
    //   - V_CURVES_CNT кривых расположены вдоль оси X на равных промежутках 
    //     в интервале шириной V_DX
    const int    V_CURVES_CNT = 5;
    const double V_DX = U_SIN_DX;
    const int    V_SIN_PERIOD_CNT = 3;
    const double V_SIN_DZ = U_DZ;
    const int    V_BEZIER_PNT_CNT = 15;
    RPArray<MbCurve3D> arrCurvesV;
    for (int i = 0; i < V_CURVES_CNT; i++)
    {
        SArray<MbCartPoint3D> arrPnts;
        for (int n = 0; n < V_BEZIER_PNT_CNT; n++)
        {
            MbCartPoint3D p;
            p.x = i * V_DX / (V_CURVES_CNT - 1);
            p.z = n * V_SIN_DZ / (V_BEZIER_PNT_CNT - 1);
            p.y = sin(p.z / V_SIN_DZ * 2 * M_PI * V_SIN_PERIOD_CNT);
            arrPnts.push_back(p);
        }
        MbBezier3D* pc = new MbBezier3D(arrPnts, false);
        arrCurvesV.Add(pc);
    }

    // Построение поверхности
    MbMeshSurface* pSurf = new MbMeshSurface(arrCurvesU, arrCurvesV,
        false, false, false);

    // Отображение поверхности
    viewManager->AddObject(Style(1, LIGHTGRAY), pSurf);

    // Отображение координатных кривых
    for (int i = 0, iLim = arrCurvesU.size(); i < iLim; i++)
        viewManager->AddObject(Style(5, LIGHTRED), arrCurvesU[i]);
    for (int i = 0, iLim = arrCurvesV.size(); i < iLim; i++)
        viewManager->AddObject(Style(5, LIGHTBLUE), arrCurvesV[i]);

    // Уменьшение счетчика ссылок динамически созданных объектов ядра
    ::DeleteItem(pSurf);
    for (int i = 0, iLim = arrCurvesU.size(); i < iLim; i++)
        ::DeleteItem(arrCurvesU[i]);
    for (int i = 0, iLim = arrCurvesV.size(); i < iLim; i++)
        ::DeleteItem(arrCurvesV[i]);

}

/////////////////////////////////////////////////////////////////////////////////

//Кинематичная поверхность (Колено)
void MakeUserCommand3()
{
    const double DEG_TO_RAD = M_PI / 180.0;
    MbPlacement3D plArc;	// СК для построения первой образующей (совпадает с мировой)
    MbPlacement3D plCurve;	// СК для построения направляющей (вычисляется далее)

    // Поворот локальной СК направляющей кривой из плоскости XY в плоскость XZ 
    // мировой системы координат
    plCurve.Rotate(MbAxis3D(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0))),
        90 * DEG_TO_RAD);

    // Построение двумерной образующей кривой - окружности
    const double RAD = 10;
    const MbCartPoint arcCenter(0, 0);
    // Построение окружности на плоскости по центру и радиусу
    MbArc* pArc2D = new MbArc(arcCenter, RAD);
    // Построение окружности в трехмерном пространстве
    MbArc3D* pArc = new MbArc3D(*pArc2D, plArc);

    // Построение направляющей кривой - дуги окружности 
    // Сначала строится дуга двумерной окружности по центру окружности, радиусу, 
    // начальной и конечной точкам
    MbArc* pCurve2D = new MbArc(MbCartPoint(-50, 0), 50, MbCartPoint(0, 0),
        MbCartPoint(-50, 50), 1);
    // Построение дуги трехмерной окружности
    MbArc3D* pCurve = new MbArc3D(*pCurve2D, plCurve);

    // Вызов функции построения кинематической поверхности
    MbSurface* pSurface = NULL;
    ::EvolutionSurface(*pArc, *pCurve, pSurface);

    // Отображение построенной поверхности
    viewManager->AddObject(Style(1, RGB(0, 0, 255)), pSurface);

    ::DeleteItem(pSurface);
    ::DeleteItem(pCurve2D);
    ::DeleteItem(pCurve);
    ::DeleteItem(pArc2D);
    ::DeleteItem(pArc);

}

/////////////////////////////////////////////////////////////////////////////////

// Вспомогательная функция.
// Построение тонкостенного твердого тела вращения в виде комбинации 
// цилиндра и сферы с центрами тяжести в начале координат.
MbSolid* CreateCylSphereSolid(double sphereRad, double cylRad, double cylHeight,
    double thwall /* толщина стенки */)
{
    // Образующая кривая: контур, состоящий из двух отрезков и дуги окружности между ними
    // Точки - вершины сегментов образующей 
    MbCartPoint3D p1(cylRad, cylHeight / 2, 0);
    MbCartPoint3D p2(cylRad, sqrt(sphereRad * sphereRad - cylRad * cylRad), 0);
    MbCartPoint3D p3(sphereRad, 0, 0);
    MbCartPoint3D p4(p2.x, -p2.y, p2.z);
    MbCartPoint3D p5(p1.x, -p1.y, p1.z);
    // Сегменты образующей кривой
    MbLineSegment3D* pSeg1 = new MbLineSegment3D(p1, p2);
    MbArc3D* pArc = new MbArc3D(p2, p3, p4, 1, false);
    MbLineSegment3D* pSeg2 = new MbLineSegment3D(p4, p5);
    // Построение образующей кривой в виде контура из трех сегментов
    RPArray<MbCurve3D> arrCurves;
    arrCurves.Add(pSeg1);
    arrCurves.Add(pArc);
    arrCurves.Add(pSeg2);
    MbContour3D* pGenContour = new MbContour3D(arrCurves, true);

    // Формирование объекта-образующей sweptData 
    RPArray< MbContour3D > arrContours;
    arrContours.Add(pGenContour);
    MbSweptData sweptData(arrContours);

    // Параметры оси вращения - ось направлена вдоль оси Y 
    MbCartPoint3D axOrg(0, 0, 0);
    MbVector3D axDir(0, 1, 0);
    MbAxis3D axRot(axOrg, axDir);

    // Именователь граней твердого тела вращения
    MbSNameMaker operNames(ct_CurveRevolutionSolid, MbSNameMaker::i_SideNone, 0);
    operNames.SetVersion(MbNameVersion());
    PArray<MbSNameMaker> cNames(0, 1, false);

    // Параметры операции вращения для построения тонкостенного тела
    RevolutionValues params;
    params.shape = 0;					// Построение тела типа "сфера"
    params.side1.scalarValue = 360 * M_PI / 180;	// Угол поворота образующей
    params.thickness1 = thwall;			// Толщина стенки

    // Вызов операции построения тела вращения pSolid
    MbSolid* pSolid = NULL;
    MbResultType res = ::RevolutionSolid(sweptData, axRot, params,
        operNames, cNames, pSolid);
    if (res != rt_Success)
    {
        // Возврат в случае ошибки при построении твердого тела
        ::DeleteItem(pGenContour);
        ::DeleteItem(pSolid);
        return NULL;
    }

    // Возврат построенного твердого тела
    return pSolid;
}

MbSolid* CreatePrismSolid(double prismSide, double prismHeight, double thwall)
{
    // Координаты вершин основания призмы (в плоскости ZY - в среднем сечении призмы)
    std::vector<MbCartPoint3D> arrPnts_Base1 = {
      { 0,  prismSide / 2, -prismSide / 2 },
      { 0,  prismSide / 2,  prismSide / 2 },
      { 0, -prismSide / 2,  prismSide / 2 },
      { 0, -prismSide / 2, -prismSide / 2 }
    };

    // Контур - замкнутая ломаная для представления основания призмы
    MbPolyline3D* pContour_Base1 = new MbPolyline3D(arrPnts_Base1, true);

    // Построение образующей кривой 
    RPArray<MbCurve3D> arrCurves;
    arrCurves.Add(pContour_Base1);
    MbContour3D* pGenContour = new MbContour3D(arrCurves, true);

    // Формирование объекта-образующей sweptData 
    RPArray< MbContour3D > arrContours;
    arrContours.Add(pGenContour);
    MbSweptData sweptData(arrContours);

    // Направление выдавливания
    MbVector3D vecDir(1, 0, 0);

    // Именователь граней твердого тела
    MbSNameMaker operNames(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 0);
    operNames.SetVersion(MbNameVersion());
    PArray<MbSNameMaker> cNames(0, 1, false);

    // Параметры операции выдавливания.
    // Выдавливание производится симметрично в обе стороны от образующей.
    ExtrusionValues params(prismHeight / 2, prismHeight / 2);
    params.thickness1 = thwall;		// Толщина стенки 

    // Вызов операции выдавливания для построения твердого тела pSolid
    MbSolid* pSolid = NULL;
    MbResultType res = ::ExtrusionSolid(sweptData, vecDir, NULL, NULL, false,
        params, operNames, cNames, pSolid);
    if (res != rt_Success)
    {
        // Возврат в случае ошибки при построении твердого тела
        ::DeleteItem(pGenContour);
        ::DeleteItem(pSolid);
        return NULL;
    }

    // Возврат построенного твердого тела
    return pSolid;
}

// Основная функция.
void MakeUserCommand4()
{
    // 1) ПОСТРОЕНИЕ ПЕРВОГО ВСПОМОГАТЕЛЬНОГО ТОНКОСТЕННОГО ТВЕРДОГО ТЕЛА 
   //    ВРАЩЕНИЯ – КОМБИНАЦИЯ ЦИЛИНДРА И СФЕРЫ
    const double CYL_RAD = 2.0;		// Радиус цилиндрической части
    const double CYL_HEIGHT = 20.0;	// Высота цилиндрической части
    const double SPHERE_RAD = 5.0;		// Радиус сферической части
    const double THICKNESS = 0.1;		// Толщина тонкой стенки
    MbSolid* pCylSphereSolid = CreateCylSphereSolid(SPHERE_RAD, CYL_RAD,
        CYL_HEIGHT, THICKNESS);
    // Возможный отладочный вызов для проверки выполнения шага 1)
    // if ( pCylSphereSolid )
    //   TestVariables::viewManager->AddObject( TestVariables::SOLID_Style, 
    //                                          pCylSphereSolid );


    // 2) ПОСТРОЕНИЕ ВТОРОГО ВСПОМОГАТЕЛЬНОГО ТОНКОСТЕННОГО ТВЕРДОГО ТЕЛА ВЫДАВЛИВАНИЯ – 
    //    БОКОВАЯ ПОВЕРХНОСТЬ ПРИЗМЫ С КВАДРАТНЫМ ОСНОВАНИЕМ
    const double PRISM_SIDE = 5;		// Сторона квадратного основания призмы
    const double PRISM_HEIGHT = 20;	// Высота призмы
    MbSolid* pPrismSolid = CreatePrismSolid(PRISM_SIDE, PRISM_HEIGHT, THICKNESS);
    // Возможный отладочный вызов для проверки выполнения шага 2)
    // if ( pPrismSolid )
    //  TestVariables::viewManager->AddObject(TestVariables::SOLID_Style, pPrismSolid);


    // 3) РАЗБИЕНИЕ ПРИЗМАТИЧЕСКОГО ТЕЛА pPrismSolid НА ТРИ ЧАСТИ: ДВЕ ЧАСТИ СНАРУЖИ
    //    И ОДНА ВНУТРИ pCylSphereSolid.
    //    ВНЕШНИЕ ЧАСТИ ОТБИРАЮТСЯ ДЛЯ ИСПОЛЬЗОВАНИЯ ПРИ ПОСТРОЕНИИ РЕЗУЛЬТИРУЮШЕГО ТЕЛА
    MbSolid* pPrismPart1 = NULL;
    MbSolid* pPrismPart2 = NULL;

    // Именователь граней для построения тела с помощью булевой операции
    MbSNameMaker operBoolNames(ct_BooleanSolid, MbSNameMaker::i_SideNone, 0);
    // Флаги операции: построение замкнутого тела с объединением подобных граней и ребер
    MbBooleanFlags flagsBool;
    flagsBool.InitBoolean(true);
    flagsBool.SetMergingFaces(true);
    flagsBool.SetMergingEdges(true);

    
        // Булева операция - разность тел: pSolidDiff = pPrismSolid - pCylSphereSolid
        // Для выполнения разности генерируется вспомогательное тело pCylSphereSolidSmall,
        // у которого радиус сферической части меньше, чем у pCylSphereSolid, на 
        // толщину стенки.
        // Это сделано для гарантированного последующего объединения частей тел в 
        // дальнейшем, на шаге 5).
        MbSolid* pCylSphereSolidSmall = CreateCylSphereSolid(SPHERE_RAD - THICKNESS,
            CYL_RAD, CYL_HEIGHT, THICKNESS);
        MbSolid* pSolidDiff = NULL;
        MbResultType res = ::BooleanResult(*pPrismSolid, cm_Copy, *pCylSphereSolidSmall,
            cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidDiff);
        ::DeleteObject(pCylSphereSolidSmall);

        // Разбиение составного тела pSolidDiff на три тела: два снаружи и одно 
        // внутри pCylSphereSolid 
        if (res == rt_Success)
        {
            RPArray<MbSolid> parts;
            MbSNameMaker detachNames(ct_DetachSolid, MbSNameMaker::i_SideNone, 0);

            // При разделении тела pSolidDiff наибольшая часть остается в pSolidDiff,
            // а меньшие (partsCnt штук) помещаются в массив parts (в порядке 
            // убывания габаритного размера)
            size_t partsCnt = ::DetachParts(*pSolidDiff, parts, true, detachNames);
            if (partsCnt == 2)
            {
                // Отбор внешних частей тела pSolidDiff
                pPrismPart1 = parts[0];
                pPrismPart2 = parts[1];
                // Удаление лишней части, которая находится внутри тела выдавливания
                ::DeleteItem(pSolidDiff);
            }
        }
    
    // 4) ВЫРЕЗАНИЕ КВАДРАТНЫХ ОТВЕРСТИЙ ИЗ pCylSphereSolid
    MbSolid* pCylSphereHolesSolid = NULL;
    {
        // Булева операция - разность тел: pSolidDiff = pCylSphereSolid - pPrismSolid
        MbSolid* pSolidDiff = NULL;
        MbResultType res = ::BooleanResult(*pCylSphereSolid, cm_Copy, *pPrismSolid,
            cm_Copy, bo_Difference, flagsBool, operBoolNames, pSolidDiff);
        // Возможный отладочный вызов для проверки выполнения шага 4)
        // if ( pSolidDiff )
        //   TestVariables::viewManager->AddObject(TestVariables::SOLID_Style, pSolidDiff);

        // Разбиение составного тела pSolidDiff на три тела
        if (res == rt_Success)
        {
            RPArray<MbSolid> parts;
            MbSNameMaker detachNames(ct_DetachSolid, MbSNameMaker::i_SideNone, 0);
            size_t partsCnt = ::DetachParts(*pSolidDiff, parts, true, detachNames);

            if (partsCnt == 2)
            {
                // Сохранение части, которая будет использоваться для результирующей модели
                pCylSphereHolesSolid = pSolidDiff;
                // Удаление частей, соответствующих квадратным отверстиям в теле вращения
                ::DeleteItem(parts[0]);
                ::DeleteItem(parts[1]);
            }
        }
    }

    // 5) ПОСТРОЕНИЕ РЕЗУЛЬТИРУЮЩЕГО ТЕЛА pResSolid: ОБЪЕДИНЕНИЕ ТРЕХ ТЕЛ 
    //    pCylSphereHolesSolid, pPrismPart1 И pPrismPart2
    MbSolid* pResSolid = NULL;
    {
        // Построение промежуточного тела: pSolid1 = pCylSphereHolesSolid + pPrismPart1
        MbSolid* pSolid1 = NULL;
        ::BooleanResult(*pCylSphereHolesSolid, cm_Copy, *pPrismPart1, cm_Copy, bo_Union,
            flagsBool, operBoolNames, pSolid1);

        // Построение результирующего тела: pResSolid = pSolid1 + pPrismPart2
        ::BooleanResult(*pSolid1, cm_Copy, *pPrismPart2, cm_Copy, bo_Union,
            flagsBool, operBoolNames, pResSolid);

        // Уменьшение счетчика ссылок промежуточного тела, которое больше не потребуется
        ::DeleteItem(pSolid1);
    }

    // ОТОБРАЖЕНИЕ РЕЗУЛЬТИРУЮЩЕГО ТВЕРДОГО ТЕЛА
    if (pResSolid)
        TestVariables::viewManager->AddObject(TestVariables::SOLID_Style, pResSolid);

    // УМЕНЬШЕНИЕ СЧЕТЧИКА ССЫЛОК ДИНАМИЧЕСКИ СОЗДАННЫХ ОБЪЕКТОВ ЯДРА
    ::DeleteItem(pCylSphereSolid);
    ::DeleteItem(pPrismSolid);
    ::DeleteItem(pPrismPart1);
    ::DeleteItem(pPrismPart2);
    ::DeleteItem(pCylSphereHolesSolid);
    ::DeleteItem(pResSolid);
}

/////////////////////////////////////////////////////////////////////////////////

void MakeUserCommand5()
{
    // Создание границ поверхности - четырех соединяющихся круговых 
  // дуг pCurve0, pCurve1, pCurve2, pCurve3.
  // Дуги строятся по трем точкам (используются начальная, средняя и 
  // конечная точка дуги).
  // При задании точек надо соблюдать направление дуг, чтобы они стыковались 
  // в одном направлении обхода.

  // Дуга в плоскости XY
    MbCartPoint3D pc01(0, 0, 0), pc02(5, 3, 0), pc03(10, 0, 0);
    MbArc3D* pCurve0 = new MbArc3D(pc01, pc02, pc03, 1, false);

    // Дуга в плоскости ZX, начинающаяся в конечной точке pc01 кривой pCurve0 
    MbCartPoint3D pc11 = pc03, pc12(7, 0, 7.5), pc13(10, 0, 15);
    MbArc3D* pCurve1 = new MbArc3D(pc11, pc12, pc13, 1, false);

    // Дуга в плоскости YX (располагается ниже плоскости ZX), начинающаяся
    // в конечной точке pCurve2.
    MbCartPoint3D pc21 = pc13, pc22(5, -3, 15), pc23(0, 0, 15);
    MbArc3D* pCurve2 = new MbArc3D(pc21, pc22, pc23, 1, false);

    // Дуга в плоскости ZX, соединяющаяся конечную точку pCurve2 с начальной 
    // точкой pCurve0. (Дуга pCurve3 зеркально симметрична для pCurve1)
    MbCartPoint3D pc31 = pc23, pc32(3, 0, 7.5), pc33 = pc01;
    MbArc3D* pCurve3 = new MbArc3D(pc31, pc32, pc33, 1, false);

    // Построение поверхности
    MbCoverSurface* pSurf = new MbCoverSurface(*pCurve0, *pCurve1, *pCurve2, *pCurve3);

    // Отображение поверхности
    viewManager->AddObject(Style(1, LIGHTGRAY), pSurf);

    // Отображение граничных кривых
    viewManager->AddObject(Style(5, LIGHTRED), pCurve0);
    viewManager->AddObject(Style(5, LIGHTRED), pCurve1);
    viewManager->AddObject(Style(5, LIGHTRED), pCurve2);
    viewManager->AddObject(Style(5, LIGHTRED), pCurve3);

    // Уменьшение счетчика ссылок динамически созданных объектов ядра
    ::DeleteItem(pSurf);
    ::DeleteItem(pCurve0);
    ::DeleteItem(pCurve1);
    ::DeleteItem(pCurve2);
    ::DeleteItem(pCurve3);

}

/////////////////////////////////////////////////////////////////////////////////


//Изогнутый правильный треугольник
void MakeUserCommand6()
{
    // Создание пересекающихся кривых pCurve0, pCurve1, pCurve2 - границ поверхности.

  // Незамкнутая кривая Безье для приближенного представления одного периода 
  // синусоиды в плоскости XY (по SIN_PNT_CNT точкам).
    SArray<MbCartPoint3D> arrPntsBezier;
    const double SIN_WIDTH = 7;
    const int SIN_PNT_CNT = 15;
    for (int i = 0; i < SIN_PNT_CNT; i++)
    {
        double x = i * 2 * M_PI / SIN_PNT_CNT;
        double y = 5 * sin(x);
        arrPntsBezier.push_back(MbCartPoint3D(x * SIN_WIDTH, y, 0));
    }
    MbBezier3D* pCurve0 = new MbBezier3D(arrPntsBezier, false);

    // Отрезок в плоскости XZ (начальная точка совпадает с начальной точкой pCurve0)
    MbLineSegment3D* pCurve1 = new MbLineSegment3D(arrPntsBezier[0],
        MbCartPoint3D(3, -1, 25));

    // Дуга окружности, соединяющая pCurve0 и pCurve1 по конечным точкам
    // Дуга строится по трем точкам. Начальная точка pc1 и конечная pc2 совпадают 
    // с конечными точками pCurve0 и pCurve1.
    // Промежуточная точка дуги в этом примере вычисляется произвольным образом 
    // (точка - центр отрезка pc1-pc3 смещается вниз по оси y).
    MbCartPoint3D pc1 = arrPntsBezier[SIN_PNT_CNT - 1];
    MbCartPoint3D pc3 = pCurve1->GetPoint2();
    MbCartPoint3D pc2;
    pc2.x = (pc1.x + pc3.x) / 2;
    pc2.y = (pc1.y + pc3.y) / 2 - 10;
    pc2.z = (pc1.z + pc3.z) / 2;
    MbArc3D* pCurve2 = new MbArc3D(pc1, pc2, pc3, 1, false);

    // Построение поверхности
    MbCornerSurface* pSurf = new MbCornerSurface(*pCurve0, *pCurve1, *pCurve2);

    // Отображение поверхности
    viewManager->AddObject(Style(1, LIGHTGRAY), pSurf);

    // Отображение граничных кривых
    viewManager->AddObject(Style(5, LIGHTRED), pCurve0);
    viewManager->AddObject(Style(5, LIGHTRED), pCurve1);
    viewManager->AddObject(Style(5, LIGHTRED), pCurve2);

    // Уменьшение счетчика ссылок динамически созданных объектов ядра
    ::DeleteItem(pSurf);
    ::DeleteItem(pCurve0);
    ::DeleteItem(pCurve1);
    ::DeleteItem(pCurve2);
}

/////////////////////////////////////////////////////////////////////////////////


//Лимон
void MakeUserCommand7()
{
    // Базовая поверхность вращения: построение по образующей, оси вращения и углу
    SArray<MbCartPoint3D> arrGenPnts(7);
    arrGenPnts.Add(MbCartPoint3D(0, 0, 0));
    arrGenPnts.Add(MbCartPoint3D(7, 10, 0));
    arrGenPnts.Add(MbCartPoint3D(0, 20, 0));
    MbBezier3D* pGenCurve = new MbBezier3D(arrGenPnts, false);
    MbAxis3D axRev(MbCartPoint3D(0, 0, 0), MbVector3D(0, 1, 0));
    MbRevolutionSurface* pBaseSurf = new MbRevolutionSurface(
        *pGenCurve, axRev, 2 * M_PI, false);
    // Отображение поверхностей
    viewManager->AddObject(Style(1, YELLOW), pBaseSurf);

    // Уменьшение счетчика ссылок динамически созданных объектов ядра
    ::DeleteItem(pGenCurve);
    ::DeleteItem(pBaseSurf);
}

/////////////////////////////////////////////////////////////////////////////////

//Ваза
void MakeUserCommand8()
{
        // Базовая поверхность вращения: построение по образующей, оси вращения и углу
    SArray<MbCartPoint3D> arrGenPnts(7);
    arrGenPnts.Add(MbCartPoint3D(0, -4.5, 0));
    arrGenPnts.Add(MbCartPoint3D(4, 10, 0));
    arrGenPnts.Add(MbCartPoint3D(0, 15, 0));

    MbBezier3D* pGenCurve = new MbBezier3D(arrGenPnts, false);
    MbAxis3D axRev(MbCartPoint3D(0, 0, 0), MbVector3D(0, 1, 0));
    MbRevolutionSurface* pBaseSurf = new MbRevolutionSurface(
        *pGenCurve, axRev, 2 * M_PI, false);

    // Построение эквидистантной поверхности 
    MbOffsetSurface* pOffSurf = new MbOffsetSurface(*pBaseSurf, 7, false);

    // Построение цилиндрической поверхности 
    double height_Cyl = -0.1;
    double radius_Cyl = 5.5;
    MbCartPoint3D baseCenter1(0, 0, 0);		// Центр первого основания 
    MbCartPoint3D baseCenter2(0, height_Cyl, 0);	// Центр второго основания 
    // Точка на втором основании для указания радиуса цилиндра
    MbCartPoint3D pntOnBase2(radius_Cyl, height_Cyl, 0);
    // Вызов функции ядра для создания элементарной поверхности
    MbSurface* pCylSurf = NULL;
    MbResultType resCylSurf = ::ElementarySurface(baseCenter1, baseCenter2, pntOnBase2,
        st_CylinderSurface, pCylSurf);

    // Построение цилиндрического тела
    MbSolid* pCyl = NULL;
    if (resCylSurf == rt_Success)
    {
        // Вспомогательный объект для именования составных элементов твердого тела
        MbSNameMaker namesCyl(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
        // Вызов функции ядра для построения тела на основе элементарной поверхности
        MbResultType resSolid = ::ElementarySolid(*pCylSurf, namesCyl, pCyl);
        if (resSolid == rt_Success)
            viewManager->AddObject(Style(1, LIGHTRED), pCyl);
    }
    viewManager->AddObject(Style(1, LIGHTGRAY), pOffSurf);

    // Уменьшение счетчика ссылок динамически созданных объектов ядра
    ::DeleteItem(pGenCurve);
    ::DeleteItem(pBaseSurf);
    ::DeleteItem(pOffSurf);
    ::DeleteItem(pCylSurf);
    ::DeleteItem(pCyl);
}

/////////////////////////////////////////////////////////////////////////////////

// Болт
void CreateSketch9(RPArray<MbContour>& _arrContours)
{
    // Центры и радиусы окружностей, дуги которых входят в контур 
    const MbCartPoint centerCircle(0, 0);
    const double RAD = 20.25;

    MbArc* pCircle = new MbArc(centerCircle, RAD);
    MbContour* pContourCircle = new MbContour(*pCircle, true);
    _arrContours.push_back(pContourCircle);
}
void CreateSketch8(RPArray<MbContour>& _arrContours)
{
    double R = 18;
    double l = 2;
    SArray<MbCartPoint>arrPnts(4);
    arrPnts.Add(MbCartPoint(-l * 0.1 + l, l + R));
    arrPnts.Add(MbCartPoint(l * 0.1 + l, l + R));
    arrPnts.Add(MbCartPoint(2 * l, -l + R));
    arrPnts.Add(MbCartPoint(0, -l + R));

    MbLineSegment* pS1 = new MbLineSegment(arrPnts[0], arrPnts[1]);
    MbContour* pContour = new MbContour(*pS1, true);

    MbLineSegment* pS2 = new MbLineSegment(arrPnts[1], arrPnts[2]);
    pContour->AddSegment(pS2);

    MbLineSegment* pS3 = new MbLineSegment(arrPnts[2], arrPnts[3]);
    pContour->AddSegment(pS3);

    MbLineSegment* pS4 = new MbLineSegment(arrPnts[3], arrPnts[0]);
    pContour->AddSegment(pS4);

    _arrContours.push_back(pContour);
}
void CreateSketch7(RPArray<MbContour>& _arrContours)
{
    // Центры и радиусы окружностей, дуги которых входят в контур 
    const MbCartPoint centerCircle(0, 0);
    const double RAD = 16.5;

    MbArc* pCircle = new MbArc(centerCircle, RAD);
    MbContour* pContourCircle = new MbContour(*pCircle, true);
    _arrContours.push_back(pContourCircle);
}
void CreateSketch6(RPArray<MbContour>& _arrContours)
{
    // Центры и радиусы окружностей, дуги которых входят в контур 
    const MbCartPoint centerCircle(0, 0);
    const double RAD = 18;
    // Количество сторон многоугольника
    const int SIDE_CNT = 6;
    // Радиус описывающей окружности многоугольника
    const double RAD1 = 45.0;

    // Массив для хранения вершин ломаной 
    SArray<MbCartPoint> arrPnts(SIDE_CNT);
    // Вычисление вершин ломаной равномерным делением окружности
    for (int i = 0; i < SIDE_CNT; i++)
    {
        // Угловое положение i-й вершины на описывающей окружности.
        // Угловое положение начальной вершины - M_PI/2 (эта вершина 
        // расположена на вертикальной оси).
        double angle = M_PI / 2 + 2 * M_PI / SIDE_CNT * i;
        MbCartPoint pnt(RAD1 * cos(angle), RAD1 * sin(angle));
        arrPnts.Add(pnt);
    }

    // Построение единой ломаной внешнего контура по точкам 
    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContour = new MbContour(*pPolyline, true);

    _arrContours.push_back(pContour);
}
void MakeUserCommand9()
{
    MbPlacement3D pl; 
    RPArray<MbContour> arrContours;
    CreateSketch6(arrContours);

    // Отображение образующей (в плоскости XY глобальной СК) 
    for (int i = 0; i < arrContours.size(); i++)
        viewManager->AddObject(Style(1, RGB(0, 0, 255)), arrContours[i], &pl);

    // ПОСТРОЕНИЕ ТЕЛА ВЫДАВЛИВАНИЯ 
    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 1, 0));

    // Объект, хранящий параметры образующей 
    MbSweptData sweptData(*pPlaneXY, arrContours);

    // Направляющий вектор для операции выдавливания 
    MbVector3D dir(0, 0, -1);

    // Параметры операции выдавливания, задающие свойства тела для построения: 
    // расстояние выдавливания в прямом и в обратном направлении вдоль 
    // направляющего вектора 
    const double HEIGHT_FORWARD = 30.0, HEIGHT_BACKWARD = 0.0;
    ExtrusionValues extrusionParam(HEIGHT_FORWARD, HEIGHT_BACKWARD);

    // Служебный объект для именования элементов модели твердого тела 
    MbSNameMaker operNames(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    // Построение твердого тела выдавливания 
    MbSolid* pSolid = NULL;
    MbResultType res = ::ExtrusionSolid(sweptData, dir, NULL, NULL, false,
        extrusionParam, operNames, cNames, pSolid);


    MbPlacement3D pl1;
    RPArray<MbContour> arrContours1;
    CreateSketch7(arrContours1);
    // Отображение образующей (в плоскости XY глобальной СК) 
    for (int i = 0; i < arrContours1.size(); i++)
        viewManager->AddObject(Style(1, RGB(0, 0, 255)), arrContours1[i], &pl1);

    // ПОСТРОЕНИЕ ТЕЛА ВЫДАВЛИВАНИЯ 
    MbPlane* pPlaneXY1 = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 1, 0));

    // Объект, хранящий параметры образующей 
    MbSweptData sweptData1(*pPlaneXY1, arrContours1);

    // Направляющий вектор для операции выдавливания 
    MbVector3D dir1(0, 0, 1);

    const double HEIGHT_FORWARD1 = 100.0, HEIGHT_BACKWARD1 = 0.0;
    // Параметры операции выдавливания, задающие свойства тела для построения: 
    // расстояние выдавливания в прямом и в обратном направлении вдоль 
    // направляющего вектора 
    ExtrusionValues extrusionParam1(HEIGHT_FORWARD1, HEIGHT_BACKWARD1);

    // Служебный объект для именования элементов модели твердого тела 
    MbSNameMaker operNames1(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames1(0, 1, false);

    // Построение твердого тела выдавливания 
    MbSolid* pSolid1 = NULL;
    MbResultType res1 = ::ExtrusionSolid(sweptData1, dir1, NULL, NULL, false,
        extrusionParam1, operNames1, cNames1, pSolid1);


    MbPlacement3D pl3;
    RPArray<MbContour> arrContours3;
    CreateSketch9(arrContours3);
    // Отображение образующей (в плоскости XY глобальной СК) 
    for (int i = 0; i < arrContours3.size(); i++)
        viewManager->AddObject(Style(1, RGB(0, 0, 255)), arrContours3[i], &pl3);

    // ПОСТРОЕНИЕ ТЕЛА ВЫДАВЛИВАНИЯ 
    MbPlane* pPlaneXY3 = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 1, 0));

    // Объект, хранящий параметры образующей 
    MbSweptData sweptData3(*pPlaneXY3, arrContours3);

    // Направляющий вектор для операции выдавливания 
    MbVector3D dir3(0, 0, 1);

    const double HEIGHT_FORWARD2 = 10.0, HEIGHT_BACKWARD2 = 0.0;
    // Параметры операции выдавливания, задающие свойства тела для построения: 
    // расстояние выдавливания в прямом и в обратном направлении вдоль 
    // направляющего вектора 
    ExtrusionValues extrusionParam3(HEIGHT_FORWARD2, HEIGHT_BACKWARD2);

    // Служебный объект для именования элементов модели твердого тела 
    MbSNameMaker operNames3(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames3(0, 1, false);

    // Построение твердого тела выдавливания 
    MbSolid* pSolid3 = NULL;
    MbResultType res3 = ::ExtrusionSolid(sweptData3, dir3, NULL, NULL, false,
        extrusionParam3, operNames3, cNames3, pSolid3);

    // Отображение построенного тела 
    if (res == rt_Success)
    {
        viewManager->AddObject(Style(1, LIGHTGRAY), pSolid);
    }
    if (res1 == rt_Success)
    {
        viewManager->AddObject(Style(1, LIGHTGRAY), pSolid1);
    }
    if (res1 == rt_Success)
    {
        viewManager->AddObject(Style(1, LIGHTGRAY), pSolid3);
    }


    // Локальная СК (по умолчанию совпадает с мировой СК)
    MbPlacement3D pl2;
    // Построение направляющей кривой в виде незамкнутого NURBS-сплайна
    // 4-го порядка по контрольным точкам
    MbConeSpiral* pSpiral = new MbConeSpiral(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, 100),
        MbCartPoint3D(0, 100, 0), 5, false);

    // Описание образующей кривой в виде плоского контура на плоскости XY мировой СК
    MbPlane* pPlaneXY2 = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, -50),
        MbCartPoint3D(0, 50, 0));
    // Построение образующей кривой с помощью вспомогательной функции CreateSketch

    RPArray<MbContour> arrContours2;
    CreateSketch8(arrContours2);
    MbSweptData sweptData2(*pPlaneXY2, arrContours2);

    // Объект с параметрами операции построения тела заметания
    EvolutionValues params2;
    // Вариант плоскопараллельного движения образующей вдоль направляющей
    params2.parallel = 1;
    // Служебные объекты-именователи для вызова геометрической операции
    MbSNameMaker operNames2(ct_CurveEvolutionSolid, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker cNames2(ct_CurveSweptSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> contourNames2(1, 0, false);
    contourNames2.Add(&cNames2);
    MbSNameMaker splineNames2(ct_CurveSweptSolid, MbSNameMaker::i_SideNone, 0);
    // Вызов операции построения тела заметания
    MbSolid* pSolid2 = NULL;
    MbResultType res2 = ::EvolutionSolid(sweptData2, *pSpiral, params2, operNames2,
        contourNames2, splineNames2, pSolid2);
    // Отображение построенного тела
    viewManager->AddObject(Style(1, LIGHTGRAY), pSolid2);
    if (res2 == rt_Success)
        viewManager->AddObject(Style(1, LIGHTGRAY), pSolid2);

    // Уменьшение счетчиков ссылок динамически созданных объектов ядра 
    ::DeleteItem(pSolid);
    ::DeleteItem(pPlaneXY);
    for (int i = 0; i < arrContours.size(); i++)
        ::DeleteItem(arrContours[i]);

    ::DeleteItem(pSolid1);
    ::DeleteItem(pPlaneXY1);
    for (int i = 0; i < arrContours1.size(); i++)
    ::DeleteItem(arrContours1[i]);

    ::DeleteItem(pSolid2);
    ::DeleteItem(pPlaneXY2);
    ::DeleteItem(pSpiral);
}

