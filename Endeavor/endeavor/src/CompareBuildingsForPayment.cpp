#include "CompareBuildingsForPayment.h"

CompareBuildingsForPayment::CompareBuildingsForPayment(EndeavorBuildingType* order)
{
   sort_order = order;
}

CompareBuildingsForPayment::~CompareBuildingsForPayment()
{}

int CompareBuildingsForPayment::findRankFromBuildingID(EndeavorBuildingType building_id)
{
   for (int i = 0; i < 12; i++)
   {
      if (sort_order[i] == building_id)
      {
         return i;
      }
   }
}

int CompareBuildingsForPayment::compare(Building* building_1, Building* building_2)
{
   EndeavorBuildingType building_1_id = building_1->getBuildingID();
   EndeavorBuildingType building_2_id = building_2->getBuildingID();

   int building_1_rank = findRankFromBuildingID(building_1_id);
   int building_2_rank = findRankFromBuildingID(building_2_id);

   return building_1_rank - building_2_rank;
}
