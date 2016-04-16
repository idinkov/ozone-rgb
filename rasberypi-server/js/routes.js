angular.module('app.routes', [])

.config(function($stateProvider, $urlRouterProvider) {

  // Ionic uses AngularUI Router which uses the concept of states
  // Learn more here: https://github.com/angular-ui/ui-router
  // Set up the various states which the app can be in.
  // Each state's controller can be found in controllers.js
  $stateProvider
    
  

      .state('controlType.colorList', {
    url: '/page1',
    views: {
      'side-menu21': {
        templateUrl: 'templates/colorList.html',
        controller: 'colorListCtrl'
      }
    }
  })

  .state('controlType.colorPicker', {
    url: '/page2',
    views: {
      'side-menu21': {
        templateUrl: 'templates/colorPicker.html',
        controller: 'colorPickerCtrl'
      }
    }
  })

  .state('controlType.partyMode', {
    url: '/party-mode',
    views: {
      'side-menu21': {
        templateUrl: 'templates/partyMode.html',
        controller: 'partyModeCtrl'
      }
    }
  })

  .state('controlType', {
    url: '/side-menu21',
    templateUrl: 'templates/controlType.html',
    abstract:true
  })

$urlRouterProvider.otherwise('/side-menu21/page1')

  

});