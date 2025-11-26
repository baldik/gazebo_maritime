#include <gz/sim/System.hh>
#include <gz/sim/Model.hh>
#include <gz/sim/Link.hh>
#include <gz/math/Pose3.hh>
#include <gz/math/Vector3.hh>
#include <gz/math/Quaternion.hh>
#include <gz/physics/World.hh>
#include <gz/physics/Model.hh>
#include <gz/physics/Link.hh>
#include <gz/plugin/Register.hh>
#include <sdf/sdf.hh>
#include <ignition/transport/Node.hh>
#include <iostream>

namespace tethys_keyboard_control
{
  class FluidDragSystem:
    public gz::sim::System,
    public gz::sim::ISystemConfigure,
    public gz::sim::ISystemPreUpdate
  {
    public: void Configure(const gz::sim::Entity &_entity,
                           const std::shared_ptr<const sdf::Element> &_sdf,
                           gz::sim::EntityComponentManager &_ecm,
                           gz::sim::EventManager &_eventMgr) override
    {
      // Load parameters from SDF
      if (_sdf->HasElement("linear_drag"))
      {
        this->linearDrag = _sdf->Get<double>("linear_drag");
      }
      if (_sdf->HasElement("angular_drag"))
      {
        this->angularDrag = _sdf->Get<double>("angular_drag");
      }
      if (_sdf->HasElement("water_density"))
      {
        this->waterDensity = _sdf->Get<double>("water_density", 1000.0);
      }
    }

    public: void PreUpdate(const gz::sim::UpdateInfo &_info,
                          gz::sim::EntityComponentManager &_ecm) override
    {
      // Only update if not paused
      if (_info.paused)
        return;

      // Iterate through all models
      _ecm.Each<gz::sim::components::Model, gz::sim::components::Name>(
        [&](const gz::sim::Entity &_entity,
            const gz::sim::components::Model *,
            const gz::sim::components::Name *_name) -> bool
        {
          // Check if this model has fluid drag enabled
          if (!_ecm.EntityHasComponentType(_entity, 
              gz::sim::components::FluidDragEnabled().TypeId()))
          {
            return true;
          }

          // Process each link in the model
          auto childLinks = _ecm.ChildrenByComponents(_entity, 
            gz::sim::components::Link());
          
          for (const auto &link : childLinks)
          {
            this->ApplyFluidDrag(_entity, link, _ecm, _info.dt);
          }

          return true;
        });
    }

    private: void ApplyFluidDrag(const gz::sim::Entity &_model,
                                const gz::sim::Entity &_link,
                                gz::sim::EntityComponentManager &_ecm,
                                double _dt)
    {
      // Get linear velocity of the link
      auto linearVel = _ecm.Component<gz::sim::components::LinearVelocity>(_link);
      if (!linearVel)
        return;

      // Get angular velocity of the link
      auto angularVel = _ecm.Component<gz::sim::components::AngularVelocity>(_link);
      if (!angularVel)
        return;

      // Get pose of the link
      auto pose = _ecm.Component<gz::sim::components::Pose>(_link);
      if (!pose)
        return;

      // Calculate drag forces
      auto linearVelValue = linearVel->Data();
      auto angularVelValue = angularVel->Data();

      // Apply linear drag (proportional to velocity)
      gz::math::Vector3d linearDragForce = -linearVelValue * this->linearDrag;

      // Apply angular drag (proportional to angular velocity)
      gz::math::Vector3d angularDragTorque = -angularVelValue * this->angularDrag;

      // Apply forces to the link
      if (auto linearForce = 
          _ecm.Component<gz::sim::components::ExternalWorldLinearForce>(_link))
      {
        linearForce->Data() += linearDragForce;
      }
      else
      {
        _ecm.CreateComponent(_link,
          gz::sim::components::ExternalWorldLinearForce(linearDragForce));
      }

      if (auto angularTorque = 
          _ecm.Component<gz::sim::components::ExternalWorldAngularTorque>(_link))
      {
        angularTorque->Data() += angularDragTorque;
      }
      else
      {
        _ecm.CreateComponent(_link,
          gz::sim::components::ExternalWorldAngularTorque(angularDragTorque));
      }
    }

    private: double linearDrag = 100.0;
    private: double angularDrag = 50.0;
    private: double waterDensity = 1000.0;
  };

  GZ_ADD_PLUGIN(FluidDragSystem, 
                gz::sim::System,
                FluidDragSystem::ISystemConfigure,
                FluidDragSystem::ISystemPreUpdate)

  GZ_ADD_PLUGIN_ALIAS(FluidDragSystem, 
                      "tethys_keyboard_control::FluidDragSystem")
}