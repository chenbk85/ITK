/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef __itkFastMarchingReachedTargetNodesStoppingCriterion_h
#define __itkFastMarchingReachedTargetNodesStoppingCriterion_h

#include "itkFastMarchingStoppingCriterionBase.h"
#include "itkObjectFactory.h"

namespace itk
{
/** \class FastMarchingReachedTargetNodesStoppingCriterion
    \brief Stopping criterion for FastMarchingFilterBase.

    Stopping criterion where the condition is satisfied when the front
    reaches one, several or all target nodes (provided by the user).

    \ingroup ITKFastMarching
*/
  template< class TInput, class TOutput >
  class FastMarchingReachedTargetNodesStoppingCriterion :
      public FastMarchingStoppingCriterionBase< TInput, TOutput >
    {
  public:
    typedef FastMarchingReachedTargetNodesStoppingCriterion       Self;
    typedef FastMarchingStoppingCriterionBase< TInput, TOutput >  Superclass;
    typedef SmartPointer< Self >                                  Pointer;
    typedef SmartPointer< const Self >                            ConstPointer;
    typedef typename Superclass::Traits                           Traits;

    /** Method for creation through the object factory. */
    itkNewMacro(Self);

    /** Run-time type information (and related methods). */
    itkTypeMacro(FastMarchingReachedTargetNodesStoppingCriterion,
                 FastMarchingStoppingCriterionBase );

    typedef typename Superclass::OutputPixelType  OutputPixelType;
    typedef typename Superclass::NodeType         NodeType;

    /** \enum TargetConditionType */
    enum TargetConditionType { OneTarget = 1,
                               SomeTargets,
                               AllTargets };

    /** Set/Get TargetCondition to indicate if the user wants the front to
    reach one, some or all target nodes. */
    void SetTargetCondition( const TargetConditionType& iCondition )
      {
      m_TargetCondition = iCondition;
      m_Initialized = false;
      this->Modified();
      }

    itkGetConstReferenceMacro( TargetCondition, TargetConditionType );

    /** Set/Get TargetOffset */
    itkSetMacro( TargetOffset, OutputPixelType );
    itkGetMacro( TargetOffset, OutputPixelType );

    /** \brief Set the number of target nodes to be reached */
    void SetNumberOfTargetsToBeReached( const size_t& iN )
      {
      m_NumberOfTargetsToBeReached = iN;
      m_Initialized = false;
      this->Modified();
      }

    /** \brief Set Target Nodes*/
    virtual void SetTargetNodes( const std::vector< NodeType >& iNodes )
      {
      m_TargetNodes = iNodes;
      m_Initialized = false;
      this->Modified();
      }

    /** \brief Set the current node */
    void SetCurrentNode( const NodeType& iNode )
      {
      if( !m_Initialized )
        {
        Initialize();
        }

      if( !m_Satisfied )
        {
        // Only check for reached targets if the mode is not NoTargets and
        // there is at least one TargetPoint.
        if ( !m_TargetNodes.empty() )
          {
          typename std::vector< NodeType >::const_iterator
              pointsIter = m_TargetNodes.begin();
          typename std::vector< NodeType >::const_iterator
              pointsEnd = m_TargetNodes.end();

          while( pointsIter != pointsEnd )
            {
            if ( *pointsIter == iNode )
              {
              this->m_ReachedTargetNodes.push_back( iNode );
              m_Satisfied =
                  ( m_ReachedTargetNodes.size() == m_NumberOfTargetsToBeReached );
              break;
              }
            ++pointsIter;
            }
          if( m_Satisfied )
            {
            m_StoppingValue = this->m_CurrentValue + m_TargetOffset;
            }
          }
        else
          {
          m_Satisfied = false;
          }
        }
      }

    /** \brief returns if the stopping condition is satisfied or not. */
    bool IsSatisfied() const
      {
      return m_Satisfied && ( this->m_CurrentValue >= m_StoppingValue );
      }

    /** \brief Get a short description of the stopping criterion. */
    std::string GetDescription() const
      {
      return "Target Nodes Reached with possible overshoot";
      }

  protected:

    /** Constructor */
    FastMarchingReachedTargetNodesStoppingCriterion() : Superclass()
      {
      m_TargetCondition = AllTargets;
      m_TargetOffset = NumericTraits< OutputPixelType >::Zero;
      m_StoppingValue = NumericTraits< OutputPixelType >::Zero;
      m_Satisfied = false;
      m_Initialized = false;
      }

    /** Destructor */
    ~FastMarchingReachedTargetNodesStoppingCriterion() {}

    TargetConditionType     m_TargetCondition;
    std::vector< NodeType > m_TargetNodes;
    std::vector< NodeType > m_ReachedTargetNodes;
    size_t                  m_NumberOfTargetsToBeReached;
    OutputPixelType         m_TargetOffset;
    OutputPixelType         m_StoppingValue;
    bool                    m_Satisfied;
    bool                    m_Initialized;

    void Reset()
      {
      this->Initialize();
      }

    void Initialize()
      {
      if( m_TargetCondition == OneTarget )
        {
        m_NumberOfTargetsToBeReached = 1;
        }
      if( m_TargetCondition == AllTargets )
        {
        m_NumberOfTargetsToBeReached = m_TargetNodes.size();
        }
      if( m_NumberOfTargetsToBeReached < 1 )
        {
        itkExceptionMacro(
              <<"Number of target nodes to be reached is null" );
        }
      if( m_NumberOfTargetsToBeReached > m_TargetNodes.size() )
        {
        itkExceptionMacro(
          <<"Number of target nodes to be reached is above the provided number of           target nodes" );
        }
      m_ReachedTargetNodes.clear();

      m_Satisfied = false;
      m_Initialized = true;
      }

  private:
    FastMarchingReachedTargetNodesStoppingCriterion( const Self& );
    void operator = ( const Self& );
    };
}
#endif // __itkFastMarchingThresholdStoppingCriterion_h
