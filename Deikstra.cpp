#include <iostream>
#include <unordered_map>

//Global value with all created Edges
std::unordered_map<std::string, class Edge*> AllEdges;


class Edge
{
protected:
    std::string Name;
    short Cost = -999;
    std::vector<std::string> Neigbours;
    
public:
    Edge ( std::string Name, short Cost )
    {
        this->Name = Name;
        this->Cost = Cost;
        AllEdges.emplace ( this->Name, this );
    };
    Edge ( std::string Name )
    {
        this->Name = Name;
    };
    Edge ();

    short GetCost ()
    {
        return this->Cost;
    }
    std::string GetName () const
    {
        return this->Name;
    }
    void AddNeighbours( const Edge &Friend)
    {
        this->Neigbours.emplace_back(Friend.GetName());
    }
    std::vector<std::string> GetNeighbours ()
    {
        return Neigbours;
    }
};

class Cost
{
protected:
    std::unordered_map<std::string, short> CostTable;
 public:   
    Cost ();

    Cost ( std::string Name, short Cost )
    {
        CostTable.emplace ( Name, Cost );
    };

    void AddEdge ( std::string Name, short  Cost )
    {
        this->CostTable.emplace ( Name, Cost );
    };
    void AddEdge ( Edge edge )
    {
        this->CostTable.emplace ( edge.GetName(), edge.GetCost());
    };

    short GetCostByName ( std::string Name )
    {
        return  CostTable[Name];
    };

    void ClearTable ()
    {
        CostTable.clear ();
    };

};


int main()
{

    Edge A ( "A" ,1); //Start Edge
    Edge B ( "B", 2 );
    Edge C ( "C", 3 );
    Edge D ( "D" ,1); // Finsih Edge

    A.AddNeighbours ( B );
    A.AddNeighbours ( C );

    B.AddNeighbours ( C );
    B.AddNeighbours ( A );
    B.AddNeighbours ( D );

    C.AddNeighbours ( B );
    C.AddNeighbours ( A );
    C.AddNeighbours ( D );

    D.AddNeighbours ( C );
    D.AddNeighbours ( B );

    Cost Cost;

    Edge StartEdge;

    std::cout << "Enter the Edge for Start : ";
    std::string Answer;
    std::cin >> Answer;

    std::cout << "Enter the Edge to Finish : ";
    std::string Finish;
    std::cin >> Finish;
    for (const auto& Element : AllEdges)
    {
        if (Answer == Element.first)
            StartEdge = *Element.second;
    }
 
    Edge CurrentEdge = StartEdge;


    bool bStart = true;
    int TotalSteps = 0;

    while (bStart)
    {
        std::vector<std::string> CurrentNeighbours = CurrentEdge.GetNeighbours ();
        std::string ClosestEdge = "None";
        int ShortestWay = std::numeric_limits<short>::max();
        for (const auto& Edges : CurrentNeighbours)
        {
            if (Edges != StartEdge.GetName ())
            {
                if (AllEdges[Edges] != nullptr)
                {
                    Cost.AddEdge ( *AllEdges[Edges] );
                }
                    short Temp = Cost.GetCostByName ( Edges );
                    if (ShortestWay > Temp)
                    {
                        ShortestWay = Temp;
                        ClosestEdge = Edges;
                    }
            }

        }
        TotalSteps += ShortestWay;
        std::cout << "Move from " << CurrentEdge.GetName () << " to " << ClosestEdge << std::endl;
        std::cout << "Shortes way is : " << ShortestWay << std::endl;
        if(AllEdges[ClosestEdge]!=nullptr)
        {
            CurrentEdge = *AllEdges[ClosestEdge];
        }
        if (CurrentEdge.GetName () == Finish)
        {
            bStart = false;
            std::cout << "We`re come to Finish Edge, total steps  is : " << TotalSteps;
        }
    }

    return 0;
}



Cost::Cost ()
{
}

Edge::Edge ()
{
}
