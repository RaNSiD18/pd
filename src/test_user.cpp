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

#include <math_namespace.h>
#include <last.h>

using namespace c3d;

using namespace TestVariables;


//------------------------------------------------------------------------------
// \ru Построение пользователя. \en User creation command.
// ---
void MakeUserCommand0() 
{ 
	MbPlacement3D pl; // Локальная СК (по умолчанию совпадает с мировой СК)

	// Вершины ломаной
	SArray<MbCartPoint> arrPnts(8);
	arrPnts.Add(MbCartPoint(30, 40));
	arrPnts.Add(MbCartPoint(30, 20));
	arrPnts.Add(MbCartPoint(0, 20));
	arrPnts.Add(MbCartPoint(0, 0));
	arrPnts.Add(MbCartPoint(100, 0));
	arrPnts.Add(MbCartPoint(100, 20));
	arrPnts.Add(MbCartPoint(70, 20));
	arrPnts.Add(MbCartPoint(70, 40));

	// Ломаная линия с вершинами arrPnts
	MbPolyline* pPolyline = new MbPolyline(arrPnts, false /* Флаг незамкнутой линии */);

	// Дуга окружности для замыкания ломаной.
	// При построении указывается центр, радиус, начальная и конечная точки и
	// направление обхода дуги между этими точками (значение initSense>0 соответствует
	// обходу против часовой стрелки, а initSense<0 – по часовой стрелке).
	MbCartPoint arcCenter(50, 40);
	const double RADIUS = 20;
	MbArc* pArc = new MbArc(arcCenter, RADIUS, arrPnts[7], arrPnts[0], 1 /*initSense*/);

	// Контур из двух сегментов
	MbContour* pContour = new MbContour(*pPolyline, true);
	pContour->AddSegment(pArc);

	// Отображение контура
	if (pContour)
		viewManager->AddObject(Style(1, RGB(0, 0, 255)), pContour, &pl);

	// Вызовы информационных методов контура
	size_t segmentsCount = pContour->GetSegmentsCount(); // 2
	double tMin = pContour->GetTMin(); // 0.0
	double tMax = pContour->GetTMax(); // 10.14159

	// Параметр IsSmoothConnected - допуск для классификации угловых точек на контуре
	bool isSmooth = pContour->IsSmoothConnected(0.001); // false
	double length = pContour->CalculateLength(tMin, tMax); // 302.83
	bool isClosed = pContour->IsClosedContinuousC0(); // true
	bool isCurvilinear = pContour->IsAnyCurvilinear(); // true

	// Уменьшение счетчиков ссылок динамически созданных объектов ядра
	::DeleteItem(pPolyline);
	::DeleteItem(pArc);
	::DeleteItem(pContour);
}



//Создание твердотельной модели усеченной пирамиды
void CreateSketch(RPArray<MbContour>& _arrContours)
{
    // Создание массива точек квадрата, к которому в дальнейшем добавятся скругления.
 // Размер массива - 8 точек для учета точек четырех сегментов скруглений.
    SArray<MbCartPoint> arrPnts(8);
    arrPnts.Add(MbCartPoint(0, 0));
    arrPnts.Add(MbCartPoint(50, 0));
    arrPnts.Add(MbCartPoint(50, 50));
    arrPnts.Add(MbCartPoint(0, 50));
    // Построение единой ломаной внешнего контура по точкам
    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = NULL;
    // Задание скругления с использованием функции FilletPolyContour
    ::FilletPolyContour(pPolyline, 5, false, arrPnts[4], pContourPolyline);
    // Задание индексов точек, в которых будет задаваться скругление с учетом
    // добавления новой точки при скруглении с использованием функции FilletTwoSegments
    ptrdiff_t idxSideRight1 = 0;
    ptrdiff_t idxSideRight2 = 2;
    ptrdiff_t idxSideRight3 = 4;
    // Добавление скруглений
    pContourPolyline->FilletTwoSegments(idxSideRight1, 5);
    pContourPolyline->FilletTwoSegments(idxSideRight2, 5);
    pContourPolyline->FilletTwoSegments(idxSideRight3, 5);
    _arrContours.push_back(pContourPolyline);
}
void MakeUserCommand1()
{
   /* void CreateSketch(RPArray<MbContour> & _arrContours)

    {

        // Создание массива точек квадрата, к которому в дальнейшем добавятся скругления.

        // Размер массива - 8 точек для учета точек четырех сегментов скруглений.

        SArray<MbCartPoint>arrPnts(8);

        arrPnts.Add(MbCartPoint(0, 0));

        arrPnts.Add(MbCartPoint(50, 0));

        arrPnts.Add(MbCartPoint(50, 50));

        arrPnts.Add(MbCartPoint(0, 50));

        // Построение единой ломаной внешнего контура по точкам

        MbPolyline* pPolyline = new MbPolyline(arrPnts, true);

        MbContour* pContourPolyline = new MbContour(*pPolyline, true);

        _arrContours.push_back(pContourPolyline);

    }*/
    // Локальная СК (по умолчанию совпадает с мировой СК)

    MbPlacement3D pl;

    // Создание образующей для тела выдавливания

    RPArray<MbContour>arrContours;

    CreateSketch(arrContours);

    // Отображение образующей (в плоскости XY глобальной СК)

    for (int i = 0; i < arrContours.size(); i++)

        viewManager->AddObject(Style(1, LIGHTRED), arrContours[i], &pl);

    // ПОСТРОЕНИЕ ТЕЛА ВЫДАВЛИВАНИЯ

    // Образующая размещается на плоскости XY глобальной СК.

    // Важное замечание: объект-плоскость должен создаваться динамически,

    // поскольку он продолжает использоваться в объекте-твердом теле после

    // выхода из данной функции.

    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0),

        MbCartPoint3D(1, 0, 0),

        MbCartPoint3D(0, 1, 0));

    // Объект, хранящий параметры образующей

    MbSweptData sweptData(*pPlaneXY, arrContours);

    // Направляющий вектор для операции выдавливания

    MbVector3D dir(0, 0, -1);

    // Параметры операции выдавливания, задающие свойства тела для построения в прямом

    // и в обратном направлении вдоль (глубина выдавливания и уклон).

    const double HEIGHT_FORWARD = 60.0, HEIGHT_BACKWARD = 0.0;

    const double ANGLE_FORWARD_DEGREE = 15.0;

    ExtrusionValues extrusionParams(HEIGHT_FORWARD, HEIGHT_BACKWARD);

    // Указание уклона для выдавливания в прямом направлении

    extrusionParams.side1.rake = ANGLE_FORWARD_DEGREE * M_PI / 180.0;

    // Именователи элементов модели твердого тела и контуров образующей

    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);

    PArray<MbSNameMaker>cNames(0, 1, false);

    // Вызов функции-утилиты для построения твердого тела выдавливания

    MbSolid* pSolid = NULL;

    MbResultType res = ::ExtrusionSolid(sweptData, dir, NULL, NULL, false,

        extrusionParams, operNames, cNames, pSolid);

    // Отображениепостроенноготела

    if (res == rt_Success)

    {

        // Смещение тела по оси Y, чтобы при отображении оно не накладывалось на образующую

        pSolid->Move(MbVector3D(0, 0, 0));

        viewManager->AddObject(Style(1, LIGHTGRAY), pSolid);

    }

    // Уменьшение счетчиков ссылок динамически созданных объектов ядра

    ::DeleteItem(pSolid);

}

}

   /* void MakeUserCommand0()

    {

        
    
 }*/

//Создание эскиза из точек усеченной пирамиды
void MakeUserCommand2()
{
    MbPlacement3D pl; // Локальная СК (по умолчанию совпадает с мировой СК)

    //Массив из точек
    SArray<MbCartPoint3D> arrPnts(8);
    arrPnts.Add(MbCartPoint3D(0, 0, 0));
    arrPnts.Add(MbCartPoint3D(0, 50, 0));
    arrPnts.Add(MbCartPoint3D(50, 50, 0));
    arrPnts.Add(MbCartPoint3D(50, 0, 0));
    arrPnts.Add(MbCartPoint3D(15, 15, 40));
    arrPnts.Add(MbCartPoint3D(15, 35, 40));
    arrPnts.Add(MbCartPoint3D(35, 35, 40));
    arrPnts.Add(MbCartPoint3D(35, 15, 40));

    //Выделения массива точек синим цветом
    viewManager->AddObject(Style(1, BLUE), new MbPointFrame(arrPnts));
}


//Создание твердотельной модели усеченной пирамиды
void CreateSketch1(RPArray<MbContour>& _arrContours)
{
    // Количество сторон многоугольника
    const int SIDE_CNT = 9;
    // Радиус описывающей окружности многоугольника
    const double RAD = 10.0;
    // Массив для хранения вершин ломаной
    SArray<MbCartPoint> arrPnts(SIDE_CNT);
    // Вычисление вершин ломаной равномерным делением окружности
    for (int i = 0; i < SIDE_CNT; i++)
    {
        // Угловое положение i-й вершины на описывающей окружности.
        // Угловое положение начальной вершины - M_PI/2 (эта вершина
        // расположена на вертикальной оси).
        double angle = M_PI / 2 + 2 * M_PI / SIDE_CNT * i;
        MbCartPoint pnt(RAD * cos(angle), RAD * sin(angle));
        arrPnts.Add(pnt);

        double angle1 = M_PI * 1.2 / 2 + 2 * M_PI / SIDE_CNT * i;
        MbCartPoint pnt1((RAD - 5) * cos(angle1), (RAD - 5) * sin(angle1));
        arrPnts.Add(pnt1);
    }

    // Замкнутая ломаная линия с вершинами arrPnts
    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = NULL;
    _arrContours.push_back(pContourPolyline);
}
void MakeUserCommand3() 
{
    // Локальная СК (по умолчанию совпадает с мировой СК)
    MbPlacement3D pl;

    // Создание образующей для тела выдавливания
    RPArray<MbContour> arrContours;
    CreateSketch1(arrContours);

    // Отображение образующей (в плоскости XY глобальной СК)
    for (int i = 0; i < arrContours.size(); i++)
        viewManager->AddObject(Style(1, LIGHTRED), arrContours[i], &pl);

    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0),
        MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 1, 0));

    // Объект, хранящий параметры образующей
    MbSweptData sweptData(*pPlaneXY, arrContours);

    // Направляющий вектор для операции выдавливания
    MbVector3D dir(0, 0, -1);

    // Параметры операции выдавливания, задающие свойства тела для построения в прямом
    // и в обратном направлении вдоль (глубина выдавливания и уклон).
    const double HEIGHT_FORWARD = 10.0, HEIGHT_BACKWARD = 0.0;
    const double ANGLE_FORWARD_DEGREE = 15.0;
    ExtrusionValues extrusionParams(HEIGHT_FORWARD, HEIGHT_BACKWARD);

    // Указание уклона для выдавливания в прямом направлении
    extrusionParams.side1.rake = ANGLE_FORWARD_DEGREE * M_PI / 180.0;

    // Именователи элементов модели твердого тела и контуров образующей
    MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    // Вызов функции-утилиты для построения твердого тела выдавливания
    MbSolid* pSolid = NULL;
    MbResultType res = ::ExtrusionSolid(sweptData, dir, NULL, NULL, false,
        extrusionParams, operNames, cNames, pSolid);

      // Отображение построенного тела
    if (res == rt_Success)
    {
        // Смещение тела по оси Y, чтобы при отображении оно не накладывалось на образующую
        pSolid->Move(MbVector3D(0, 0, 0));
        viewManager->AddObject(Style(1, LIGHTGRAY), pSolid);
    }
    // Уменьшение счетчиков ссылок динамически созданных объектов ядра
    ::DeleteItem(pSolid);
}


// Построение параллелепипеда с отверстием при помощи инструмента выдавливания
void CreateSketch2(RPArray<MbContour>& _arrContours)
{
    // Центры и радиусы окружностей, дуги которых входят в контур 
    const MbCartPoint centerCircle(25, 25);
    const double RAD = 10;
    // Создание массива точек квадрата, к которому в дальнейшем добавятся скругления. 
    // Размер массива - 8 точек для учета точек четырех сегментов скруглений. 
    SArray<MbCartPoint> arrPnts(8);
    arrPnts.Add(MbCartPoint(0, 0));
    arrPnts.Add(MbCartPoint(50, 0));
    arrPnts.Add(MbCartPoint(50, 50));
    arrPnts.Add(MbCartPoint(0, 50));
    // Построение единой ломаной внешнего контура по точкам 
    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContour = new MbContour(*pPolyline, true);


    MbArc* pCircle = new MbArc(centerCircle, RAD);
    MbContour* pContourCircle = new MbContour(*pCircle, true);
    _arrContours.push_back(pContour);
    _arrContours.push_back(pContourCircle);
}
void MakeUserCommand4() 
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
        const double HEIGHT_FORWARD = 100.0, HEIGHT_BACKWARD = 0.0;
        ExtrusionValues extrusionParam(HEIGHT_FORWARD, HEIGHT_BACKWARD);

        // Служебный объект для именования элементов модели твердого тела 
        MbSNameMaker operNames(ct_CurveExtrusionSolid, MbSNameMaker::i_SideNone, 0);
        PArray<MbSNameMaker> cNames(0, 1, false);

        // Построение твердого тела выдавливания 
        MbSolid* pSolid = NULL;
        MbResultType res = ::ExtrusionSolid(sweptData, dir, NULL, NULL, false,
            extrusionParam, operNames, cNames, pSolid);

        // Отображение построенного тела 
        if (res == rt_Success)
        {
            // Смещение тела по оси Y, чтобы при отображении оно не накладывалось на образующую 
            pSolid->Move(MbVector3D(0, 80, 0));
            viewManager->AddObject(Style(1, LIGHTGRAY), pSolid);
        }

        // Уменьшение счетчиков ссылок динамически созданных объектов ядра 
        ::DeleteItem(pSolid);
        ::DeleteItem(pPlaneXY);
        for (int i = 0; i < arrContours.size(); i++)
            ::DeleteItem(arrContours[i]);
}


// Построение цилиндра с помощью функции вращения
void CreateSketch3(RPArray<MbContour>& _arrContours)
{
    // Создание массива точек квадрата, к которому в дальнейшем добавятся скругления.
    // Размер массива - 8 точек для учета точек четырех сегментов скруглений.
    SArray<MbCartPoint> arrPnts(4);
    arrPnts.Add(MbCartPoint(0, 0));
    arrPnts.Add(MbCartPoint(50, 0));
    arrPnts.Add(MbCartPoint(50, 50));
    arrPnts.Add(MbCartPoint(0, 50));
    // Построение единой ломаной внешнего контура по точкам
    MbPolyline* pPolyline = new MbPolyline(arrPnts, true);
    MbContour* pContourPolyline = new MbContour(*pPolyline, true);
    _arrContours.push_back(pContourPolyline);
}
void MakeUserCommand5() 
{
        // Множитель для преобразования угловых значений из градусов в радианы
        const double DEG_TO_RAD = M_PI / 180.0;
        // Локальная СК (по умолчанию совпадает с мировой СК)
        MbPlacement3D pl;
        // Вызов функции для построения образующей (из примера 4.1)
        RPArray<MbContour> arrContours;
        CreateSketch3(arrContours);
        // Отображение образующей (в плоскости XY глобальной СК)
        for (int i = 0; i < arrContours.size(); i++)
            viewManager->AddObject(Style(1, RGB(0, 0, 255)), arrContours[i], &pl);
        // Подготовка параметров для вызова функции построения тела вращения.
        // sweptData - объект, в котором хранятся сведения об образующей.
        MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0),
            MbCartPoint3D(0, 1, 0));
        MbSweptData sweptData(*pPlaneXY, arrContours);
        // Объект параметров для операции построения тела вращения.
        // Первые два параметра конструктора задают углы вращения в прямом и обратном
        // направлении (по нормали к образующей или противоположно этой нормали).
        // В данном примере вращение осуществляется на 120 градусов в прямом направлении.
        // Третий параметр задает форму топологии твердого тела.
        // При s = 0 строится тело с топологией сферы, при s = 1 - с топологией тора.
        // Если образующая - незамкнутая кривая, и ось вращения лежит в плоскости кривой,
        // то при s = 0 при построении образующая будет автоматически продлена до оси
        // вращения. В данном примере различий между значениями s нет, т.к. образующая
        // имеет вид замкнутого контура.
        RevolutionValues revParms(360 * DEG_TO_RAD, 0, 0);
        // Именователи для операции построения тела вращения и для контуров образующей
        MbSNameMaker operNames(1, MbSNameMaker::i_SideNone, 0);
        PArray<MbSNameMaker> cNames(0, 1, false);
        // Ось вращения для построения тела:
        // ось Y мировой СК смещается на -50 единиц вдоль оси X.
        MbAxis3D axis(pl.GetAxisY());
        // Вызов функции-утилиты для построения твердого тела вращения
        MbSolid* pSolid = NULL;
        MbResultType res = ::RevolutionSolid(sweptData, axis, revParms,
            operNames, cNames, pSolid);
        // Отображение построенного тела
        if (res == rt_Success)
            viewManager->AddObject(Style(1, LIGHTGRAY), pSolid);
        // Уменьшение счетчиков ссылок динамических объектов ядра
        ::DeleteItem(pSolid);
}


//------------------------------------------------------------------------------
// \ru Построение пользователя. \en User creation command.
// ---
void MakeUserCommand6() 
{
    // Сферическая поверхность - построение по центру и радиусу
    MbSphereSurface* pSurf = new MbSphereSurface(MbCartPoint3D(50, 0, 0), 20);
    // Отображение поверхности
    viewManager->AddObject(Style(1, LIGHTGRAY), pSurf);
    // Уменьшение счетчика ссылок динамически созданных объектов ядра
    ::DeleteItem(pSurf);


    // Цилиндрическая поверхность - построение по трем точкам
    const MbCartPoint3D p0(50, 0, 0); // Центр локальной СК цилиндра (центр основания)
    const MbCartPoint3D p1(0, 20, 0); // Вектор p0-p1 задает ось Z локальной СК
    // и высоту цилиндра
    const MbCartPoint3D p2(10, 0, 0); // Вектор p0-p2 задает ось X локальной СК и
    // радиус основания
    MbCylinderSurface* pSurf1 = new MbCylinderSurface(p0, p1, p2);
    // Отображение поверхности
    viewManager->AddObject(Style(1, LIGHTGRAY), pSurf1);
    // Уменьшение счетчика ссылок динамически созданных объектов ядра
    ::DeleteItem(pSurf1);


    // Коническая поверхность - конструктор по локальной системе координат,
// радиусу, углу и высоте.
    const MbPlacement3D pl1; // Локальная СК совпадает с мировой
    const double radius = 0; // Радиус в плоскости XY локальной СК
    // (если 0 - строится коническая поверхность конуса,
    // если >0 - строится поверхность усеченного конуса)
    // Угол между осью Z локальной СК и боковой образующей
    const double angle = 22.5 * M_PI / 180.0;
    const double height = 10; // Высота конуса (вдоль оси Z)
    MbConeSurface* pSurf2 = new MbConeSurface(pl1, radius, angle, height);
    // Отображение поверхности
    viewManager->AddObject(Style(1, LIGHTGRAY), pSurf2);
    // Уменьшение счетчика ссылок динамически созданных объектов ядра
    ::DeleteItem(pSurf2);


    // Тороидальная поверхность: конструктор по локальной СК и двум радиусам
// Ось Z локальной СК является осью вращательной симметрии торической поверхности
    const MbPlacement3D pl2; // Локальная СК совпадает с мировой.
    const double radius1 = 10; // Радиус центров трубки тора
    const double radius2 = 3; // Радиус трубки тора
    MbTorusSurface* pSurf3 = new MbTorusSurface(pl2, radius1, radius2);
    // Отображение поверхности
    viewManager->AddObject(Style(1, LIGHTGRAY), pSurf3);
    // Уменьшение счетчика ссылок динамически созданных объектов ядра
    ::DeleteItem(pSurf3);

}


//------------------------------------------------------------------------------
// \ru Построение пользователя. \en User creation command.
// ---
void MakeUserCommand7() 
{
    // Локальная СК (по умолчанию совпадает с мировой СК)
    MbPlacement3D pl;
    // Массив контрольных точек для построения NURBS-сплайна
    std::vector<MbCartPoint3D> vecPnts = { { 0, 0, 0 }, { 0, 0, 150 } };
    SArray<MbCartPoint3D> arrPnts(vecPnts);
    // Построение направляющей кривой в виде незамкнутого NURBS-сплайна
    // 2-го порядка по контрольным точкам
    MbNurbs3D* pSpline = MbNurbs3D::Create(2, arrPnts, false);
    // Описание образующей кривой в виде плоского контура на плоскости XY мировой СК
    MbPlane* pPlaneXY = new MbPlane(MbCartPoint3D(0, 0, 0), MbCartPoint3D(1, 0, 0),
        MbCartPoint3D(0, 1, 0));
    // Построение образующей кривой с помощью вспомогательной функции CreateSketch
    RPArray<MbContour> arrContours;
    CreateSketch(arrContours);
    MbSweptData sweptData(*pPlaneXY, arrContours);
    // Объект с параметрами операции построения тела заметания
    EvolutionValues params;
    // Вариант плоскопараллельного движения образующей вдоль направляющей
    params.parallel = 0;
    // Служебные объекты-именователи для вызова геометрической операции
    MbSNameMaker operNames(ct_CurveEvolutionSolid, MbSNameMaker::i_SideNone, 0);
    MbSNameMaker cNames(ct_CurveSweptSolid, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> contourNames(1, 0, false);
    contourNames.Add(&cNames);
    MbSNameMaker splineNames(ct_CurveSweptSolid, MbSNameMaker::i_SideNone, 0);
    // Вызов операции построения тела заметания
    MbSolid* pSolid = NULL;
    MbResultType res = ::EvolutionSolid(sweptData, *pSpline, params, operNames,
        contourNames, splineNames, pSolid);
    // Отображение построенного тела
    if (res == rt_Success)
        viewManager->AddObject(Style(1, LIGHTGRAY), pSolid);
    // Отображение направляющей кривой со смещением вдоль оси Y (в целях отображения,
    // чтобы отображаемая кривая была смещена от поверхности тела).
    pSpline->Move(MbVector3D(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, -50, 0)));
    viewManager->AddObject(Style(3, RGB(0, 0, 255)), pSpline, &pl);
    // Уменьшение счетчиков ссылок объектов ядра
    ::DeleteItem(pSolid);
    ::DeleteItem(pPlaneXY);
    ::DeleteItem(pSpline);
}


//------------------------------------------------------------------------------
// \ru Построение пользователя. \en User creation command.
// ---
void MakeUserCommand8() 
{
  ::PutErrorMessage( 0, RT_MAKE_USER_COMAND_8 );
}


//------------------------------------------------------------------------------
// \ru Построение пользователя. \en User creation command.
// ---
void MakeUserCommand9() 
{
  ::PutErrorMessage( 0, RT_MAKE_USER_COMAND_9 );
}
