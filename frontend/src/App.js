import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css'
import { BrowserRouter as Router, Route } from 'react-router-dom'

import Navigation from './components/Navigation'
import RAM from './components/ChartRam'
import CPU from './components/TableCpu'

/*
import NotesList from './components/NotesList'
import CreateNote from './components/CreateNote'

*/
import './App.css';

function App() {
  return (
    <Router>
      <Navigation />
      <div className="container p-4">
        {<Route path="/" exact component={RAM} />}
        {<Route path="/" exact component={CPU} />}
        {}
        {/*<Route path="/create" exact component={CreateCar} />*/}
        {/*<Route path="/edit/:id" component={CreateNote} />
        <Route path="/create" component={CreateNote} />
  */}
      </div>
    </Router>
  );
}

export default App;