Info<< "\nConstructing carrier fields for cloud" << endl;

// For cloud
volScalarField& Tref = thermo.T();

// PtrList<volScalarField>& Yef = composition.Y();

volScalarField rhoC
(
    IOobject
    (
        "rhoC",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    rho
);

volVectorField UC
(
    IOobject
    (
        "UC",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    U
);

Info<< "\nConstructing coal cloud" << endl;
biomassMSCCloud bioCloud
(
    "bioCloud",
    rhoC,
    UC,
    g,
    slgThermo
);
