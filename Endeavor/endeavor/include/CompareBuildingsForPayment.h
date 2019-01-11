#if !defined (COMPAREBUILDINGSFORPAYMENT_H)
#define COMPAREPAYMENTBUILDINGSFORPAYMENT_H

#include "Comparator.h"
#include "Building.h"

class CompareBuildingsForPayment : public Comparator<Building>
{ 
   private:
      EndeavorBuildingType* sort_order;

      int findRankFromBuildingID(EndeavorBuildingType building_id);

   public:
      CompareBuildingsForPayment(EndeavorBuildingType* sort_order);
      virtual ~CompareBuildingsForPayment();

      virtual int compare(Building* building_1, Building* building_2);
};

#endif
