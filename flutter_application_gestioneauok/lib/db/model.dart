import 'package:flutter/cupertino.dart';

class GestionModel{

 double? taux_r;

double? volume;

  GestionModel({@required this.taux_r,@required this.volume,});


//-------------------------------------convert to json-----------------------------------------------------------
  Map<String,dynamic> tojson(){
    return {
        'taux_r': taux_r,
        'volume': volume,
     

    };
  }
  //------------------------------------ adapte json to our local model --------------------------------------------------------------------------- 

 factory GestionModel.formJson(Map<String,dynamic> json){
  return GestionModel(taux_r: json["taux_r"], volume: json["volume"]);
}

}