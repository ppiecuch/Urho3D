//
// Copyright (c) 2008-2016 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../../Precompiled.h"

#include "../../Graphics/Material.h"
#include "../../Graphics/Model.h"
#include "../../Graphics/StaticModel.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(StaticModelApplyMaterialList, StaticModel, ApplyMaterialList, 0, 1);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(StaticModelGetMaterial, StaticModel, GetMaterial, 0, 1);

static void StaticModelMaterialSetter(StaticModel* self, Material* material)
{
    self->SetMaterial(material);
}

static Material* StaticModelMaterialGetter(const StaticModel* self)
{
    return self->GetMaterial();
}

void RegisterStaticModel(kaguya::State& lua)
{
    using namespace kaguya;

    lua["StaticModel"].setClass(UserdataMetatable<StaticModel, Drawable>()
        .addStaticFunction("new", &CreateObject<StaticModel>)

        .addFunction("SetModel", &StaticModel::SetModel)

        .addOverloadedFunctions("SetMaterial",
            static_cast<void(StaticModel::*)(Material*)>(&StaticModel::SetMaterial),
            static_cast<bool(StaticModel::*)(unsigned, Material*)>(&StaticModel::SetMaterial))

        .addFunction("SetOcclusionLodLevel", &StaticModel::SetOcclusionLodLevel)
        
        .addFunction("ApplyMaterialList", StaticModelApplyMaterialList())

        .addFunction("GetModel", &StaticModel::GetModel)
        .addFunction("GetNumGeometries", &StaticModel::GetNumGeometries)

        .addFunction("GetMaterial", StaticModelGetMaterial())
        
        .addFunction("GetOcclusionLodLevel", &StaticModel::GetOcclusionLodLevel)
        .addFunction("IsInside", &StaticModel::IsInside)
        .addFunction("IsInsideLocal", &StaticModel::IsInsideLocal)

        .addProperty("model", &StaticModel::GetModel, &StaticModel::SetModel)

        .addProperty("material", &StaticModelMaterialGetter, &StaticModelMaterialSetter)

        .addProperty("numGeometries", &StaticModel::GetNumGeometries)
        .addProperty("occlusionLodLevel", &StaticModel::GetOcclusionLodLevel, &StaticModel::SetOcclusionLodLevel)
        );
}
}
